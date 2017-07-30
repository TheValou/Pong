#include "client.h"


void		check_cmd(char *buffer, t_data *data)
{
  char		**play;
  int		i;

  i = 0;
  play = my_str_to_wordtab(buffer, '\n');
  while (play[i] != NULL)
  {
    if (strncmp(play[i], "SCORE", 5) == 0)
     my_scores(play[i], data);
   else if (strncmp(play[i], "PLAYERS", 7) == 0)
     my_players(play[i], data);
   else if (strncmp(play[i], "BALL", 4) == 0)
     my_ball(play[i], data);
   i++;
 }
}

void    my_players(char *buffer, t_data * data)
{
  char    **tab;

  tab = my_str_to_wordtab(buffer, ' ');
  if (atoi(tab[1]) == data->id)
  {
    data->xplayer = atof(tab[1]) * 15;
    data->yplayer = (data->height - atof(tab[2]) - 1) * 15;
  }
  else if (atoi(tab[1]) != data->id)
  {
    data->xplayertwo = atof(tab[3]) * 15;
    data->yplayertwo = (data->height - atof(tab[4]) - 1) * 15;
  }
}

void    my_scores(char *buffer, t_data * data)
{
  char    **tab;

  tab = my_str_to_wordtab(buffer, ' ');
  data->scorep1 = atoi(tab[1]);
  data->scorep2 = atoi(tab[2]);
}

void    my_ball(char *buffer, t_data *data)
{
  char    **tab;

  tab = my_str_to_wordtab(buffer, ' ');
  data->ball_x = atoi(tab[1]);
  data->ball_y = atoi(tab[2]);
}

