#include "client.h"
#include <stdio.h>
#include <string.h>

pthread_cond_t condition = PTHREAD_COND_INITIALIZER; /* Création de la condition */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /* Création du mutex */

void	do_client(t_data *data)
{
  char    str[512];
  int   rread;

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
            puts("avant le puts");

      puts(str);
      data->game = str;
      check_cmd(str, data);
      memset(str, 0, 512);
    }
  }
}

void      *display(void *arg)
{
  t_data      *data;
  t_display   *display;

  data = malloc(sizeof(t_data));
  display = malloc(sizeof(t_display));
  if (data == NULL || display == NULL)
  {
    fprintf(stderr, "Erreur\n");
    exit (1);
  }
  data = (t_data *)arg;

  if (init_sdl(display, data) == 1)
    return (NULL);
  else
    sdl_start(display, data);
  pthread_exit(NULL);
  return (NULL);
}

void	*my_client(void *arg)
{
  int	connect;
  
  t_data    *data;
  data = malloc(sizeof(t_data));
  if (data == NULL)
  {
    fprintf(stderr, "Erreur d'allocation pour data\n");
    exit (1);
  }
  data = (t_data *)arg;

  data->type = 1;
  data->port = atoi(data->argv[5]);

  data->pe = getprotobyname("TCP");
  data->socket = my_socket(AF_INET, SOCK_STREAM, data->pe->p_proto);
  if (data->socket == -1)
    return (NULL);
  data->sin.sin_family = AF_INET;
  data->sin.sin_addr.s_addr = inet_addr(data->argv[3]);
  data->sin.sin_port = htons(data->port);
  connect = my_connect(data->socket, (const struct sockaddr *)&data->sin, sizeof(data->sin));
  if (connect != -1)
  {
    do_client(data);
    close(data->socket);
  }
  else
    free(data);
  pthread_exit(NULL);
  exit(-1);
  return (NULL);
}

int     client(t_data *data)
{
  pthread_t   print;
  pthread_t   client;

  pthread_create(&client, NULL, &my_client, data);
  pthread_create(&print, NULL, display, data);
  pthread_join(client, NULL);
  pthread_join(print, NULL);
  return (0);
}




