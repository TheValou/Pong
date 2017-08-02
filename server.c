/*
** server.c for soft war in /home/wurfl_v/Soft War/Serveur
** 
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
** 
** Started on  Wed Jul  6 09:59:13 2016 WURFL Valentin
** Last update Sat Jul 29 15:55:30 2017 WURFL Valentin
*/

#include "client.h"

void    check_client(char *buffer, t_data *data)
{
  char    **play;
  int   i;

  (void)data;
  i = 0;
  play = my_str_to_wordtab(buffer, '\n');
  while (play[i] != NULL)
  {
    if (strncmp(play[i], "UP 1", 4) == 0)
    {
      if(data->yplayer>=5)
        data->yplayer -=5;
    }
    if (strncmp(play[i], "DOWN 1", 6) == 0)
    {
      if(data->yplayer<=SCREEN_H -BAR_H -5)
        data->yplayer +=5;
    }    
    i++;
  }
  free(play);
}


void    connect_client(t_server *server, t_data *data)
{
 struct sockaddr_in csin;
 size_t size;
 int     cs;
 char    str[512]; //Message envoyé par le client
 int   rread;

 char sendc[512]; //chaine à renvoyer

 char scoreP1_s[10]; //score du p1 en char*
 char scoreP2_s[10]; //score du p2 en char*


 char P1_x[10];
 char P1_y[10];
 char P2_x[10];
 char P2_y[10];

 char Ball_x_s[10];
 char Ball_y_s[10];

 size = sizeof(csin);
 cs = accept(server->fd_socket, (struct sockaddr *)&csin, (socklen_t *)&size);
 if (cs > 0)
 {
   while (42)
   {
    if ((rread = recv(cs, str, 510, 0)) < 0)
    {
      perror("recv()");
      exit(errno);
    }
    str[rread] = '\0';

    if (strlen(str) <= 250)
    {
      puts(str);
      memset(sendc, 0, 512);

      check_client(str, data);

      /* Rebond sur les bords de l'ecran VITESSSSE*/ 
      if(data->ball_y <=0)
        data->yBall = BALL_SPEED; //va vers le bas
      if(data->ball_y >=SCREEN_H)
        data->yBall = -BALL_SPEED; //va vers le haut

      


      /* Si victoire d'un joueur */
      if(data->ball_x <=0)
      {
        resetBallserv(&data->ball_x,&data->ball_y,&data->xBall,&data->yBall);
        data->scorep2++;
      }
      if(data->ball_x + BALL_SIZE >SCREEN_W)
      {
        resetBallserv(&data->ball_x,&data->ball_y,&data->xBall,&data->yBall);
        data->scorep1++;
      }      
      
      
      /* Collision avec la barre de gauche */
      if(data->ball_x <= data->xplayer+BAR_W && data->ball_x > data->xplayer)
      {

        if(data->ball_y >= data->yplayer && data->ball_y <= data->yplayer + BAR_H)
          data->xBall = BALL_SPEED;
      }

      /* Collision avec la barre de droite */
      if(data->ball_x >= data->xplayertwo &&  data->ball_x < data->xplayertwo + BAR_W/2)
      {
        if(data->ball_y >= data->yplayertwo && data->ball_y <= data->yplayertwo + BAR_H)
          data->xBall = -BALL_SPEED;
      }

      data->ball_x += data->xBall;
      data->ball_y += data->yBall;

/* Mise a jour du score OKAY*/
      sprintf(scoreP1_s,"%d",data->scorep1);
      sprintf(scoreP2_s,"%d",data->scorep2);

      strcat(sendc, "SCORE ");
      strcat(sendc, scoreP1_s);
      strcat(sendc, " ");
      strcat(sendc, scoreP2_s);
    /* Mise a jour du score */

      sprintf(Ball_x_s,"%d",data->ball_x);
      sprintf(Ball_y_s,"%d",data->ball_y);

      strcat(sendc, "\nBALL ");
      strcat(sendc, Ball_x_s);
      strcat(sendc, " ");
      strcat(sendc, Ball_y_s);

      printf("à envoyer = %s\n", sendc);

      if(send(cs, sendc, strlen(sendc), 0) < 0)
      {
        perror("send()");
        exit(errno);
      }

      //write vers le client le tableau avec toutes les infos
      memset(str, 0, 512);
      memset(sendc, 0, 512);
    }
  }
}

}

int   init_connection(t_server *server, int port)
{
  server->pe = getprotobyname("TCP");
  server->fd_socket = my_socket(AF_INET, SOCK_STREAM, server->pe->p_proto);

  if (server->fd_socket != -1)
  {
    server->sin.sin_family = AF_INET;
    server->sin.sin_port = htons(port);
    server->sin.sin_addr.s_addr = INADDR_ANY;
    return (1);
  }
  return (-1);
}

void     *my_server(void *arg)
{
  t_server    *server;
  int     port;
  t_data    *data;
  data = malloc(sizeof(t_data));
  if (data == NULL)
  {
    fprintf(stderr, "Erreur d'allocation pour data\n");
    exit (1);
  }
  data = (t_data *)arg;

  data->type = 2;

  //init_data(data);

  server = malloc(sizeof(t_server));
  if (server == NULL)
    return (NULL);
  port = atoi(data->argv[3]);
  if (init_connection(server, port) != -1)
  {
    if((my_bind(server->fd_socket, (const struct sockaddr *)&server->sin, sizeof(server->sin)) != -1))
    {
     my_listen(server->fd_socket, 4);
     connect_client(server, data);
     close(server->fd_socket);
     return (NULL);
   }
 }
 return (NULL);
}

int     server(t_data *data) //OKAY
{
  pthread_t   print;
  pthread_t   server;

  pthread_create(&server, NULL, &my_server, data);
  pthread_create(&print, NULL, display, data);

  pthread_join(server, NULL);
  pthread_join(print, NULL);
  return (0);
}



