/*
** my_errors.c for soft war in /home/wurfl_v/Soft War/Client
** 
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
** 
** Started on  Wed Jul  6 09:56:52 2016 WURFL Valentin
** Last update Sat Jul 29 15:22:02 2017 WURFL Valentin
*/

#include <stdio.h>
#include <errno.h>
#include "client.h"

int     my_socket(int domain, int type, int protocol)
{
  int   ret;

  ret = socket(domain, type, protocol);
  if (ret == -1)
    {
      write(2, "Error with socket\n", my_strlen("Error with socket\n"));
      perror("");
    }
  return (ret);
}

int	my_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int   ret;

  ret = connect(sockfd, addr, addrlen);
  if (ret == -1)
    {
      write(2, "Error with connect\n", my_strlen("Error with connect\n"));
      perror("");
      close(sockfd);

    }
  return (ret);
}

int		my_read(int fd, void *buffer, size_t count)
{
  int		ret;

  ret = read(fd, buffer, count);
  if (ret <= 0)
    {
      write(2, "Error with read\n", my_strlen("Error with read\n"));
      perror("");
    }
  return (ret);
}
