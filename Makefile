##
## Makefile for soft war in /home/wurfl_v/Soft War/Client
##
## Made by WURFL Valentin
## Login   <wurfl_v@etna-alternance.net>
##
## Started on  Wed Jul  6 09:56:29 2016 WURFL Valentin
## Last update Sun Jul 30 18:38:20 2017 WURFL Valentin
##

NAME = pong

SRC  =  main.c \
	client.c \
	my_errors.c \
	init_sdl.c \
	commands.c \
	my_str_to_wordtab.c \
	server.c

RM= rm -f

CC= gcc

OBJ=   $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -W -Werror -pedantic

LDFLAGS = -lpthread -lSDL -lSDL_image -lSDL_ttf

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LDFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re