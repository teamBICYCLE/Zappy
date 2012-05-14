##
## Makefile for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
## 
## Made by Jonathan Machado
## Login   <jonathan.machado@epitech.net>
## 
## Started on  Sat May 12 14:30:37 2012 Jonathan Machado
## Last update Mon May 14 20:33:08 2012 Jonathan Machado
##

CC		= gcc

NAME		= zappyd

SRCS_DIR	= srcs/
INC_DIR		= includes/ 
OBJS_DIR	= objs/

CFLAGS		+= -W -Wall -Werror -O3
IFLAGS		+= -I $(INC_DIR) -I lib
LFLAGS		+= -Llib -ldata

SRCS		+= $(wildcard $(SRCS_DIR)*.c)

INCLUDES	+= $(wildcard $(INC_DIR)*.h)

OBJS		= $(SRCS:%.c=%.o)
OBJS		:= $(notdir $(OBJS))
OBJS		:= $(addprefix $(OBJS_DIR), $(OBJS))

$(NAME)		: lib $(OBJS)
		  $(CC) -o $(NAME) $(OBJS) $(LFLAGS)

$(OBJS_DIR)%.o	: $(SRCS_DIR)%.c $(INCLUDES)
		  $(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

all		: $(NAME)

lib		:
		make -C lib

clean		:
		  $(RM) $(OBJS)
		  $(RM) *~ \#*\#

fclean		: clean
		  $(RM) $(NAME)

re		: fclean all

.PHONY		: all clean fclean re