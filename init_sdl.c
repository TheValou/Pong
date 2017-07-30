/*
** init.c for client in /home/wurfl_v/jetpack2Tek3/client
**
** Made by wurfl_v
** Login   <wurfl_v@epitech.net>
**
** Started on  Wed Jul 22 11:18:39 2015 wurfl_v
** Last update Thu Jul 23 16:45:24 2015 wurfl_v
*/

#include "client.h"

int	init_sdl(t_display *display) //FONCTION BONNE
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
  SDL_FillRect(display->ligne,NULL,SDL_MapRGB(display->ligne->format,100,100,100)); //ON DESSINE LA LIGNE CENTRALE, OKAY

  display->rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE,BAR_W,BAR_H,32,0,0,0,0);
  SDL_FillRect(display->rectangle,NULL,SDL_MapRGB(display->rectangle->format,255,255,255));
  
  display->player1 = SDL_CreateRGBSurface(SDL_HWSURFACE,BAR_W,BAR_H,32,0,0,0,0);
  SDL_FillRect(display->player1,NULL,SDL_MapRGB(display->player1->format,255,255,255));

  display->player2 = SDL_CreateRGBSurface(SDL_HWSURFACE,BAR_W,BAR_H,32,0,0,0,0);
  SDL_FillRect(display->player2,NULL,SDL_MapRGB(display->player2->format,255,255,255));

  display->ball = SDL_CreateRGBSurface(SDL_HWSURFACE,BALL_SIZE,BALL_SIZE,32,0,0,0,0);
  SDL_FillRect(display->ball,NULL,SDL_MapRGB(display->ball->format,255,255,255)); //ON DESSINE LA BALL, OKAY


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
  
  display->positionP2.x = SCREEN_W - 50 - BAR_W;
  display->positionP2.y = SCREEN_H/2 - BAR_H/2;
  
  display->xBall = 0;
  display->yBall = 0;

  resetBall(&display->positionBall,&display->xBall,&display->yBall);
  
  display->positionLigne.x = SCREEN_W/2 - LINE_W/2;
  display->positionLigne.y = 0;


  return (0);
}



void    print_ball(t_data *data, t_display *display) //Pour aficcher la ball de PONG, OKAY
{
  display->positionBall.x = data->ball_x;
  display->positionBall.y = data->ball_y;
  SDL_BlitSurface(display->ball, NULL, display->ecran, &display->positionBall);
}

void    print_players(t_data *data, t_display *display) //Pour aficche rles joueurs de PONG, À MODIFIER!!
{
  SDL_Rect  position;

  position.x = data->xplayer;
  if (data->yplayer <= 1)
    position.y = (data->height - 1) * 15;
  else
    position.y = data->yplayer;
  SDL_FillRect(display->rectangle, NULL, SDL_MapRGB(display->ecran->format, 240, 5, 0));
  SDL_BlitSurface(display->rectangle, NULL, display->ecran, &position);
  
  position.x = data->xplayertwo;
  if (data->yplayertwo <= 1)
    position.y = (data->height - 1) * 15;
  else
    position.y = data->yplayertwo;
  SDL_FillRect(display->rectangle, NULL, SDL_MapRGB(display->ecran->format, 5, 245, 0));
  SDL_BlitSurface(display->rectangle, NULL, display->ecran, &position);
}

void  wait_event(t_display *display, t_data *data) //ATTENDRE LES ÉVENEMENTS, fonction bone, à tester
{
  SDL_PollEvent(&display->event);
  if (display->event.type == SDL_QUIT)
  {
    SDL_Quit();
    exit(0);
  }
  if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_ESCAPE)
  {
    SDL_Quit();
    exit(0);
  }
  if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_UP)
    dprintf(data->socket, "UP 1\n");
  if (display->event.type == SDL_KEYUP && display->event.key.keysym.sym == SDLK_UP)
    dprintf(data->socket, "UP 0\n");
  if (display->event.type == SDL_KEYDOWN && display->event.key.keysym.sym == SDLK_DOWN)
    dprintf(data->socket, "DOWN 1\n");
  if (display->event.type == SDL_KEYUP && display->event.key.keysym.sym == SDLK_DOWN)
    dprintf(data->socket, "DOWN 0\n");
  SDL_Delay(20);
}

int   sdl_start(t_display *display, t_data *data) //Lancer le jeu
{
  int   continuer = 1;

  while (continuer)
  {
    wait_event(display, data);
      draw_game(display, data); //affichage des joueurs et de la balle
    }
    SDL_FreeSurface(display->rectangle);
    SDL_Quit();
    return (0);
  }

  void    draw_game(t_display *display, t_data *data) //pour afficher le jeu, à modifier
  {

 /* Affichage des surfaces */
    SDL_FillRect(display->ecran,NULL,SDL_MapRGB(display->ecran->format,0,0,0));
    SDL_BlitSurface(display->ligne,NULL,display->ecran,&display->positionLigne);
    
    SDL_BlitSurface(display->player1,NULL,display->ecran,&display->positionP1);
    SDL_BlitSurface(display->player2,NULL,display->ecran,&display->positionP2);
    
    SDL_BlitSurface(display->score1,NULL,display->ecran,&display->positionScore1);
    SDL_BlitSurface(display->score2,NULL,display->ecran,&display->positionScore2);
    (void)data;

    // print_players(data, display);
    //print_ball(data, display);
    // print_score(data, display);
    
    SDL_Flip(display->ecran);
    SDL_Delay(10);

  }

/* Relance la balle */
  void resetBall(SDL_Rect *position,int *x,int *y)
  {
    position->x  = BALL_X;
    position->y = BALL_Y;
    *x=BALL_SPEED;
    *y=BALL_SPEED;
  }

