/*
** functions2.c for soft war in /home/wurfl_v/Soft War/Client
**
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
**
** Started on  Wed Jul  6 09:55:59 2016 WURFL Valentin
** Last update Wed Jul  6 09:56:00 2016 WURFL Valentin
*/

#include "client.h"

int	my_getnbr(char *str)
{
  int	result;
  int	count;
  int	i;

  i = 0;
  count = 1;
  result = 0;
  while (str[i] < '0' || str[i] > '9')
    {
      if (str[i] != '-' && str[i] != '+')
	return (0);
      if (str[i] == '-')
	count = count * -1;
      i++;
    }
  while ((str[i] >= '0' && str[i] <= '9'))
    {
      result = result * 10;
      result = result + (str[i] - 48);
      i++;
    }
  result = result * count;
  return (result);
}

void		my_memset(char *str, int c, size_t n)
{
  size_t	i;

  i = 0;
  while (str[i] != '\0' && i < n)
    {
      str[i] = c;
      i++;
    }
}

void		get_next_line(const int fd)
{
  char		*buffer;
  int		rread ;

  buffer = malloc(sizeof(char*) * (BUFFER_SIZE + 1));
  rread = read(fd, buffer, BUFFER_SIZE);
  if (rread == -1)
      return ;
  buffer[BUFFER_SIZE] = '\0';
  while (rread > 0 && buffer[my_strlen(buffer) - 1] != '\n')
    {
      my_putstr(buffer);
      my_memset(buffer, 0, BUFFER_SIZE);
      rread = read(fd, buffer, BUFFER_SIZE);
      buffer[BUFFER_SIZE] = '\0';
    }
  my_putstr(buffer);
  my_memset(buffer, 0, BUFFER_SIZE);
  free(buffer);
}
