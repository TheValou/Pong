/*
** init.c for client in /home/wurfl_v/jetpack2Tek3/client
**
** Made by wurfl_v
** Login   <wurfl_v@epitech.net>
**
** Started on  Wed Jul 22 11:18:39 2015 wurfl_v
** Last update Sat Aug  5 00:52:08 2017 WURFL Valentin
*/

#include "client.h"

int	init_sdl(t_display *display, t_data *data)
{
  display->ecran = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
  {
    fprintf(stderr, "erreur d'initialisation SDL\n");
    return (1);
  }
  display->ecran = SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (display->ecran == NULL)
  {
    SDL_Quit();
    fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
    return (1);
  }
  SDL_WM_SetCaption("Pong", NULL);
  display->keystates = SDL_GetKeyState(NULL);

  display->ligne = SDL_CreateRGBSurface(SDL_HWSURFACE,LINE_W,SCREEN_H,32,0,0,0,0);
  SDL_FillRect(display->ligne,NULL,SDL_MapRGB(display->ligne->format,100,100,100));

  display->rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,BAR_W,BAR_H,32,0,0,0,0);
  SDL_FillRect(display->rectangle,NULL,SDL_MapRGB(display->rectangle->format,255,255,255));

  display->player1 = SDL_CreateRGBSurface(SDL_HWSURFACE,BAR_W,BAR_H,32,0,0,0,0);
  SDL_FillRect(display->player1,NULL,SDL_MapRGB(display->player1->format,255,255,255));

  display->player2 = SDL_CreateRGBSurface(SDL_HWSURFACE,BAR_W,BAR_H,32,0,0,0,0);
  SDL_FillRect(display->player2,NULL,SDL_MapRGB(display->player2->format,255,255,255));

  display->ball = SDL_CreateRGBSurface(SDL_HWSURFACE,BALL_SIZE,BALL_SIZE,32,0,0,0,0);
  SDL_FillRect(display->ball,NULL,SDL_MapRGB(display->ball->format,255,255,255));

  TTF_Init();

  display->font = TTF_OpenFont("DS-DIGI.TTF", 30);

  display->couleur.r = 255;
  display->couleur.g = 255;
  display->couleur.b = 255;

  display->positionScore1.x = SCREEN_W/2 - 100 ;
  display->positionScore1.y = SCORE_D ;

  display->positionScore2.x = SCREEN_W/2 + 100 ;
  display->positionScore2.y = SCORE_D ;

  SDL_EnableKeyRepeat(10, 50);

  /* Placement des barres, balle et ligne */
  display->positionP1.x = 50;
  display->positionP1.y = SCREEN_H/2 - BAR_H/2;

  data->xplayer = display->positionP1.x;
  data->yplayer = display->positionP1.y;

  display->positionP2.x = SCREEN_W - 50 - BAR_W;
  display->positionP2.y = SCREEN_H/2 - BAR_H/2;

  data->xplayertwo = display->positionP2.x;
  data->yplayertwo = display->positionP2.y;

  display->xBall = 0;
  display->yBall = 0;

  resetBall(&display->positionBall,&data->xBall,&data->yBall);

  data->ball_x = display->positionBall.x;
  data->ball_y = display->positionBall.y;

  display->positionLigne.x = SCREEN_W/2 - LINE_W/2;
  display->positionLigne.y = 0;
  return (0);
}

void    print_ball(t_data *data, t_display *display)
{
  display->positionBall.x = data->ball_x;
  display->positionBall.y = data->ball_y;
  SDL_BlitSurface(display->ball,NULL,display->ecran,&display->positionBall);
}

void    print_players(t_data *data, t_display *display)
{
  display->positionP1.x = data->xplayer;
  display->positionP1.y = data->yplayer;
  SDL_FillRect(display->player1, NULL, SDL_MapRGB(display->ecran->format, 240, 5, 0));
  SDL_BlitSurface(display->player1, NULL, display->ecran, &display->positionP1);

  display->positionP2.x = data->xplayertwo;
  display->positionP2.y = data->yplayertwo;
  SDL_FillRect(display->player2, NULL, SDL_MapRGB(display->ecran->format, 240, 5, 0));
  SDL_BlitSurface(display->player2, NULL, display->ecran, &display->positionP2);
}

void	wait_event(t_display *display, t_data *data)
{
  SDL_PollEvent(&display->event);
  if (display->event.type == SDL_QUIT)
  {
    SDL_Quit();
    exit(0);
  }
  else if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_ESCAPE)
  {
    SDL_Quit();
    exit(0);
  }
  else if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_UP) {
    dprintf(data->socket, "UP 1\n");
  }
  else if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_DOWN) {
    dprintf(data->socket, "DOWN 1\n");
  }
  else {
    dprintf(data->socket, "PLOP");
  }
  SDL_Delay(20);
}

void	wait_event_serve(t_display *display, t_data *data)
{
  SDL_PollEvent(&display->event);
  if (display->event.type == SDL_QUIT)
  {
    SDL_Quit();
    exit(0);
  }
  else if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_ESCAPE)
  {
    SDL_Quit();
    exit(0);
  }
  else if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_UP)
  {
    if(data->yplayertwo >= 5)
      data->yplayertwo -=5;
  }
  else if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_DOWN)
  {
    if(data->yplayertwo<=SCREEN_H -BAR_H -5)
      data->yplayertwo +=5;
  }
  else
  {

  }
  SDL_Delay(20);
}

int	sdl_start(t_display *display, t_data *data) /* Lancer le jeu */
{
  int   continuer;

  continuer = 1;
  while (continuer)
  {
    if (data->type == 1)
      wait_event(display, data);
    if (data->type == 2)
      wait_event_serve(display, data);
      draw_game(display, data); /* affichage des joueurs et de la balle */
  }
  SDL_Quit();
  return (0);
}

  void		draw_game(t_display *display, t_data *data) /* pour afficher le jeu */
{

  char		scoreP1_s[10];
  char		scoreP2_s[10];

  sprintf(scoreP1_s,"%d",data->scorep1);
  sprintf(scoreP2_s,"%d",data->scorep2);

  display->score1 = TTF_RenderText_Solid(display->font, scoreP1_s, display->couleur);
  display->score2 = TTF_RenderText_Solid(display->font, scoreP2_s, display->couleur);

  SDL_FillRect(display->ecran,NULL,SDL_MapRGB(display->ecran->format,0,0,0));
  SDL_BlitSurface(display->ligne,NULL,display->ecran,&display->positionLigne);

  print_ball(data, display);
  SDL_BlitSurface(display->score1,NULL,display->ecran,&display->positionScore1);
  SDL_BlitSurface(display->score2,NULL,display->ecran,&display->positionScore2);

  print_players(data, display);
  SDL_Flip(display->ecran);
  SDL_Delay(10);
}

  /* Relance la balle */
void	resetBall(SDL_Rect *position,int *x,int *y)
{
  position->x  = BALL_X;
  position->y = BALL_Y;
  *x=BALL_SPEED;
  *y=BALL_SPEED;
}

void	resetBallserv(int *pos_x,int *pos_y,int *x,int *y)
{
  *pos_x  = BALL_X;
  *pos_y = BALL_Y;
  *x=BALL_SPEED;
  *y=BALL_SPEED;
}
