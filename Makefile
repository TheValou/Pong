##
## Makefile for soft war in /home/wurfl_v/Soft War/Client
## 
## Made by WURFL Valentin
## Login   <wurfl_v@etna-alternance.net>
## 
## Started on  Wed Jul  6 09:56:29 2016 WURFL Valentin
## Last update Sat Jul 29 15:17:27 2017 WURFL Valentin
##

NAME = pong

SRC  =  main.c \
	client.c \
	my_errors.c \
	functions.c \
	functions2.c

RM= rm -f

CC= gcc

OBJ=   $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -W -Werror -pedantic

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
