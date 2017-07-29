/*
** client.c for soft war in /home/wurfl_v/Soft War/Client
** 
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
** 
** Started on  Wed Jul  6 09:55:31 2016 WURFL Valentin
** Last update Sat Jul 29 15:37:29 2017 WURFL Valentin
*/

#include "client.h"
#include <stdio.h>

void	do_client(t_data *data)
{
  char	*buffer;
  int	quit;

  quit = 1;
  buffer = malloc(sizeof(char *) * 251);
  get_next_line(data->socket);
  /* write(data->socket, "Jean-Pierre", my_strlen("Jean-Pierre")); */
  while (quit == 1)
    {
      if (my_read(0, buffer, 251) <= 0)
	  quit = 0;
      else if (my_strlen(buffer) <= 250)
	{
	  if (my_strncmp(buffer, "/bye\n", 5) == 0)
	      quit = 0;
	  else
	    {
	      write(data->socket, buffer, my_strlen(buffer));
	      get_next_line(data->socket);
	    }
	}
      my_memset(buffer, 0, 251);
    }
  free(buffer);
  free(data);
}

void	my_client(t_data *data)
{
  int	connect;

  data->port = my_getnbr(data->argv[5]);
  printf("Port = %d\n", atoi(data->argv[5]));
  data->pe = getprotobyname("TCP");
  data->socket = my_socket(AF_INET, SOCK_STREAM, data->pe->p_proto);
  if (data->socket == -1)
    return ;
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
  return ;
}
