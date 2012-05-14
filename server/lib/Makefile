##
## Makefile for  in /home/jonathan/Projets/Tek-2/C/myscript-2015-2014s-machad_j
## 
## Made by Jonathan Machado
## Login   <jonathan.machado@epitech.net>
## 
## Started on  Mon Feb 20 15:07:55 2012 Jonathan Machado
## Last update Fri Apr 20 18:06:26 2012 Jonathan Machado
##

NAME		= libdata.a
CC		= gcc
SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)
CFLAGS		= -W -Wall -Werror -pedantic -ansi -ggdb
LFLAGS		= -W -Wall -Werror -pedantic -ansi

$(NAME)		: $(OBJS)
		ar rc  $(NAME) $(OBJS)
		ranlib  $(NAME)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: clean all

.PHONY		: all clean fclean re