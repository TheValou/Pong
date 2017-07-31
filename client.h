/*
** client.h for soft war in /home/wurfl_v/Soft War/Client
**
** Made by WURFL Valentin
** Login   <wurfl_v@etna-alternance.net>
**
** Started on  Wed Jul  6 09:57:37 2016 WURFL Valentin
** Last update Sat Jul 29 16:56:34 2017 WURFL Valentin
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

# include <sys/types.h>
# include <sys/socket.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <errno.h>
# include <strings.h>
# include <string.h>
# include <pthread.h>
# include <SDL/SDL.h>
# include <SDL/SDL_ttf.h>


#define	BUFFER_SIZE 50

#define SCREEN_W 800
#define SCREEN_H 480

#define BAR_W 15
#define BAR_H 120

#define LINE_W 2

#define BALL_X 100
#define BALL_Y 100
#define BALL_SIZE 10
#define BALL_SPEED 5

#define SCORE_D 30

typedef struct		s_data
{
	struct sockaddr_in	sin;
	struct protoent		*pe;
	int 				type;
	int					port;
	int					socket;
	char 				*game;
	int					height;
	int					width;
	int					id;
	int					scorep1;
	int					scorep2;
	int 				ball_x; /*position*/
	int 				ball_y; /*posotion*/

   int xBall;/*vitesse*/
    int yBall;/*viteesse*/

	int				xplayer;
	int				yplayer;
	int				xplayertwo;
	int				yplayertwo;

	char			**argv;
}			t_data;

typedef	struct	s_display
{
	SDL_Surface	*ecran;
	SDL_Surface	*ball;
    SDL_Surface	*rectangle;/* bar = NULL, */
    SDL_Surface	*player2;/* bar = NULL, */
    SDL_Surface	*player1;/* bar = NULL, */
    SDL_Surface *ligne;

    Uint8 		*keystates;

    SDL_Rect		positionP1;
    SDL_Rect		positionP2;
    SDL_Rect		positionBall;
    SDL_Rect		positionLigne; /*FIXE*/
    SDL_Rect		positionScore1; /*FIXE*/
    SDL_Rect		positionScore2; /*FIXE*/
    SDL_Event		event;

    int xBall;/*vitesse*/
    int yBall;/*viteesse*/

    TTF_Font *font;
    SDL_Color couleur;
    SDL_Surface *score1;
    SDL_Surface *score2;

    int		width;
    int		height;
}		t_display;


/* PARTIE SERVEUR */

typedef struct		s_server
{
  struct protoent	*pe;
  struct sockaddr_in	sin;
  int			fd_max;
  int			fd_socket;
  fd_set		readf;
  int			fd_op;
}			t_server;


int	my_socket(int domain, int type, int protocol);
void	launch_game(t_server *server);
int	my_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int	my_listen(int sockfd, int backlog);
int	my_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int	my_getnbr(char *str);
void   	my_memset(char *str, int c, size_t n);
char	*my_strcpy(char *dest, char *src);
char	*my_strdup(char *str);
void	my_putchar(char c);
void	my_putstr(char *str);
int	my_strlen(char *str);
int	my_strcmp(char *s1, char *s2);
int	my_strncmp(char *s1, char *s2, int n);
void    init_ressources();
void    connect_client(t_server *server, t_data *data);
int	init_connection(t_server *server, int port);
char	*my_strcat(char *str1, char *str2);
char	*my_char_nbr(int nb);
int     server(t_data *data);

void      *display(void *arg);
/* PARTIE SERVEUR */



int		main(int argc, char **argv);
int		init_sdl(t_display *display);
void	usage();
void	*my_client(void *arg);
int		client(t_data *data);
void	do_client(t_data *data);
int		my_socket(int domain, int type, int protocol);
int		my_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int		my_read(int fd, void *buffer, size_t count);
int		check_arg(int argc, char **argv);
void	my_putchar(char c);
void	my_putstr(char *str);
int		my_strlen(char *str);
int		my_strcmp(char *s1, char *s2);
int		my_strncmp(char *s1, char *s2, int n);
int		my_getnbr(char *str);
void	my_memset(char *str, int c, size_t n);
void	get_next_line(const int fd);
void    draw_game(t_display *display, t_data *data);
void		check_cmd(char *buffer, t_data *data);
void    my_players(char *buffer, t_data * data);
void    my_scores(char *buffer, t_data * data);
void    my_ball(char *buffer, t_data *data);
void resetBall(SDL_Rect *position,int *x,int *y);
char	**my_str_to_wordtab(char *str, char sp);
void resetBall(SDL_Rect *position,int *x,int *y);
int   sdl_start(t_display *display, t_data *data); /*Lancer le jeu*/
int			server(t_data *data);

#endif /* !CLIENT_H_*/
