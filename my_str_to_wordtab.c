/*
** my_str_to_wordtab.c for client in /home/wurfl_v/jetpack2Tek3/client
**
** Made by wurfl_v
** Login   <wurfl_v@epitech.net>
**
** Started on  Wed Jul 22 11:18:58 2015 wurfl_v
** Last update Thu Jul 23 10:11:00 2015 wurfl_v
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

char	**my_str_to_wordtab(char *str, char sp)
{
  int	i;
  int	j;
  int	x;
  char	**tab;

  if ((tab = malloc((1 + strlen(str)) * sizeof(char *))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (str[i] != '\0') {
    x = 0;
    while (str[i] != '\0' && (str[i] == sp || str[i] == ' ' || str[i] == '\t'))
      i++;
    if (str[i] != '\0' && (tab[j] = malloc(strlen(str) + 1)) == NULL)
      return (NULL);
    if (str[i] == '\0')
      return (tab);
    while (str[i] != '\0' && str[i] != sp) {
     tab[j][x] = str[i];
     x++;
     i++;
   }
   while (str[i++] != '\0' && str[i] == sp);
   tab[j++][x] = 0;
   i--;
 }
 tab[j] = NULL;
 return (tab);
}

char	**my_str_to_map(char *map, t_data *data)
{
  int	i;
  int	j;
  int	x;
  char	**tab;

  if ((tab = malloc((data->height + 1) * sizeof(char *))) == NULL)
    return (NULL);
  i = 0;
  j = 0;
  while (map[i]) {
    x = 0;
    if ((tab[j] = malloc(data->width + 1)) == NULL)
      return (NULL);
    while (map[i] && x < data->width) {
     tab[j][x] = map[i];
     x++;
     i++;
   }
   tab[j][x] = 0;
   j++;
 }
 tab[j] = NULL;
 return (tab);
}