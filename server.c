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

  i = 0;
  play = my_str_to_wordtab(buffer, '\n');
  while (play[i] != NULL)
  {
    if (strncmp(play[i], "UP 1", 5) == 0)
     my_scores(play[i], data);
   else if (strncmp(play[i], "UP 0", 7) == 0)
     my_players(play[i], data);
   else if (strncmp(play[i], "DOWN 0", 4) == 0)
     my_ball(play[i], data);
   else if (strncmp(play[i], "DOWN 1", 4) == 0)
     my_ball(play[i], data);
   i++;
 }
}


void    connect_client(t_server *server)
{
 struct sockaddr_in csin;
 size_t size;
 int     cs;
 char    str[512];
 int   rread;

 size = sizeof(csin);
 cs = accept(server->fd_socket, (struct sockaddr *)&csin, (socklen_t *)&size);
 if (cs > 0)
 {
   while (42)
   {
    if ((rread = recv(data->socket, str, 510, 0)) < 0)
    {
      perror("recv()");
      exit(errno);
    }
    str[rread] = '\0';

    if (strlen(str) <= 250)
    {
      puts(str);
      data->game = strdup(str);
      check_client(str, data);

      //MOuvement de la balle


/* Mise a jour du score */
      sprintf(scoreP1_s,"%d",scoreP1);
      sprintf(scoreP2_s,"%d",scoreP2);
  
      score1 = TTF_RenderText_Solid(font, scoreP1_s, couleurScore);
      score2 = TTF_RenderText_Solid(font, scoreP2_s, couleurScore);
      
      
      /* Rebond sur les bords de l'ecran */
      if(posBall.y <=0)
  yBall = BALL_SPEED;
      if(posBall.y >=SCREEN_H)
  yBall = -BALL_SPEED;
        
      
      
      /* Si victoire d'un joueur */
      if(posBall.x <=0)
  {
    resetBall(&posBall,&xBall,&yBall);
    scoreP2++;
  }
      if(posBall.x + BALL_SIZE >SCREEN_W)
  {
    resetBall(&posBall,&xBall,&yBall);
    scoreP1++;
  }
      
      
      
      
      /* Collision avec la barre de gauche */
      
      if(posBall.x <= posBar1.x+BAR_W &&  posBall.x > posBar1.x)
  {
      
    if(posBall.y >= posBar1.y && posBall.y <= posBar1.y + BAR_H)
      xBall = BALL_SPEED;
      
  }
      
      /* Collision avec la barre de droite */
      if(posBall.x >= posBar2.x &&  posBall.x < posBar2.x + BAR_W/2)
  {
      
    if(posBall.y >= posBar2.y && posBall.y <= posBar2.y + BAR_H)
      xBall = -BALL_SPEED;
      
  }


      //write ver sle client le tableau avec toutes les infos
      memset(str, 0, 512);
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

int     server(t_data *data)
{
  t_server    *server;
  int     port;

  server = malloc(sizeof(t_server));
  if (server == NULL)
    return (-1);
  init_ressources();
  port = my_getnbr(argv[3]);
  if (init_connection(server, port) != -1)
  {
    if( (my_bind(server->fd_socket, (const struct sockaddr *)&server->sin, sizeof(server->sin)) != -1))
    {
     my_listen(server->fd_socket, 4);
     connect_client(server);
     close(server->fd_socket);
     return (1);
   }
 }
 return (-1);
}
