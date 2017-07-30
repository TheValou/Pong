/*
** my_errors.c for soft war in /home/wurfl_v/Soft War/Client
** 
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
** 
** Started on  Wed Jul  6 09:56:52 2016 WURFL Valentin
** Last update Sat Jul 29 16:00:39 2017 WURFL Valentin
*/

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "client.h"

int     my_socket(int domain, int type, int protocol)
{
  int   ret;

  ret = socket(domain, type, protocol);
  if (ret == -1)
    {
      write(2, "Error with socket\n", strlen("Error with socket\n"));
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
      write(2, "Error with connect\n", strlen("Error with connect\n"));
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
      write(2, "Error with read\n", strlen("Error with read\n"));
      perror("");
    }
  return (ret);
}

int     my_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
  int   ret;

  ret = bind(sockfd, addr, addrlen);
  if (ret == -1)
    {
      write(2, "Error on socket\n", strlen("Error on socket\n"));
      perror("");
      close(sockfd);
    }
  return (ret);
}

int     my_listen(int sockfd, int backlog)
{
  int   ret;

  ret = listen(sockfd, backlog);
  if (ret == -1)
    {
      write(2, "Error on socket\n", strlen("Error on socket\n"));
      perror("");
      close(sockfd);
    }
  return (ret);
}