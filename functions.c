/*
** functions.c for soft war in /home/wurfl_v/Soft War/Client
**
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
**
** Started on  Wed Jul  6 09:56:13 2016 WURFL Valentin
** Last update Wed Jul  6 09:56:14 2016 WURFL Valentin
*/

#include <unistd.h>

void	my_putchar(char c)
{
  write(1, &c, 1);
}

void	my_putstr(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      my_putchar(str[i]);
      i++;
    }
}

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

int	my_strcmp(char *s1, char *s2)
{
  int	i;

  i = 0;
  while (s1[i])
    {
      if (s1[i] > s2[i])
	return (1);
      else if (s1[i] < s2[i])
	return (-1);
      i++;
    }
  if (s1[i] == '\0' && s2[i] == '\0')
    return (0);
  if (s1[i] == '\0' && s2[i] != '\0')
    return (-1);
  if (s1[i] != '\0' && s2[i] == '\0')
    return (1);
  return (0);
}

int	my_strncmp(char *s1, char *s2, int n)
{
  int	i;

  i = 0;
  while (s1[i] && i < n)
    {
      if (s1[i] > s2[i])
	return (1);
      else if (s1[i] < s2[i])
	return (-1);
      i++;
    }
  if (s1[i] == '\0' && s2[i] == '\0' && i < n)
    return (0);
  if (s1[i] == '\0' && s2[i] != '\0' && i < n)
    return (-1);
  if (s1[i] != '\0' && s2[i] == '\0' && i < n)
    return (1);
  return (0);
}
