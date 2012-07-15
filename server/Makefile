##
## Makefile for Zappy in /home/jonathan/Projets/Tek-2/C/Zappy/server
##
## Made by Jonathan Machado
## Login   <jonathan.machado@epitech.net>
##
## Started on  Sat May 12 14:30:37 2012 Jonathan Machado
## Last update Sun Jul 15 15:40:39 2012 lois burg
##

CC		= gcc

NAME		= zappyd

SRCS_DIR	= srcs/
INC_DIR		= includes/
OBJS_DIR	= objs/
LIB_DIR		= lib/

CFLAGS		+= -W -Wall -Werror
IFLAGS		+= -I $(INC_DIR) -I lib
LFLAGS		+= -Llib -ldata -lm
DFLAGS		+= -D_BSD_SOURCE -D_XOPEN_SOURCE -D_GNU_SOURCE

SRCS		+= $(wildcard $(SRCS_DIR)*.c)

LIB_SRCS	+= $(wildcard $(LIB_DIR)*.c)

INCLUDES	+= $(wildcard $(INC_DIR)*.h)

OBJS		= $(SRCS:%.c=%.o)
OBJS		:= $(notdir $(OBJS))
OBJS		:= $(addprefix $(OBJS_DIR), $(OBJS))

$(NAME)		: $(OBJS_DIR) $(OBJS) $(LIB_SRCS)
		  make -sC ./lib
		  $(CC) -o $(NAME) $(OBJS) $(LFLAGS)

$(OBJS_DIR)%.o	: $(SRCS_DIR)%.c $(INCLUDES)
		  $(CC) -c $(CFLAGS) $(DFLAGS) $(IFLAGS) $< -o $@

$(OBJS_DIR)	:
		  mkdir $(OBJS_DIR)

all		: $(NAME)

clean		:
		  $(RM) $(OBJS)
		  $(RM) *~ \#*\#

fclean		: clean
		  $(RM) $(NAME)

re		: fclean all

.PHONY		: all clean fclean re