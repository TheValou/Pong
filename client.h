/*
** client.h for soft war in /home/wurfl_v/Soft War/Client
** 
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
** 
** Started on  Wed Jul  6 09:57:37 2016 WURFL Valentin
** Last update Sat Jul 29 15:11:27 2017 WURFL Valentin
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <errno.h>

#define	BUFFER_SIZE 50

typedef struct		s_data
{
  struct sockaddr_in	sin;
  struct protoent	*pe;
  int			port;
  int			socket;
  char			**argv;
}			t_data;

int	main(int argc, char **argv);
void	usage();
void	my_client(t_data *data);
void	do_client(t_data *data);
int	my_socket(int domain, int type, int protocol);
int	my_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int	my_read(int fd, void *buffer, size_t count);
int	check_arg(int argc, char **argv);
void	my_putchar(char c);
void	my_putstr(char *str);
int	my_strlen(char *str);
int	my_strcmp(char *s1, char *s2);
int	my_strncmp(char *s1, char *s2, int n);
int	my_getnbr(char *str);
void	my_memset(char *str, int c, size_t n);
void	get_next_line(const int fd);

#endif /* !CLIENT_H_*/
