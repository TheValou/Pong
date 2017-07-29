#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "client.h"

int	check_arg(int argc, char **argv)
{
  if (argc < 4 || argc > 6)
      return (1);
  if (strcmp(argv[1], "--host") == 0)
    {
      if (my_strcmp(argv[2], "--port") != 0)
	return (1);
      if (atoi(argv[3]) < 0)
	return (1);
      return (2);
    }

  if (strcmp(argv[1], "--join") == 0)
    {
      if (strcmp(argv[2], "--ip") != 0)
	return (1);
      if (strcmp(argv[4], "--port") != 0)
	return (1);
      if (atoi(argv[5]) < 0)
	return (1);
      return (3);
    }  
  return (1);
}


void	usage()
{
  my_putstr("Arguments invalides, Usage :\n");
  my_putstr("./pong --host --port [n'importe quelle port]\n");
  my_putstr("./pong --join --ip [n'importe quelle ip] --port [n'importe quelle port]\n");
}

int		main(int argc,char **argv)
{
  t_data	*data;
  my_putstr("ici la");
  int		choice;
  
  if ((data = malloc(sizeof(t_data))) == NULL)
    return (-1);
  my_putstr("ici la mainteant");
  choice = check_arg(argc, argv);
  if (choice == 1)
    {
      usage();
      free(data);
      return (1);
    }
  data->argv = argv;
  if (choice == 3)
    my_client(data);
  return (0);
}
