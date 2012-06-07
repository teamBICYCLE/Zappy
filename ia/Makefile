##
## Makefile for  in /home/carpen_t/projets/syst_Unix/nibbler-2015-burg_l
##
## Made by thibault carpentier
## Login   <carpen_t@epitech.net>
##
## Started on  Sun Mar 11 12:01:22 2012 thibault carpentier
## Last update Thu Jun  7 09:38:29 2012 thibault carpentier
##

NAME		=	iabomber

CXX		=	g++
RM		=	rm -f

INCLUDE_DIR	=	./headers/
INCLUDE		=	-I$(INCLUDE_DIR)
INCLUDE		+=

INCLUDE_LST	=	$(INCLUDE_DIR)luainc.hh		\
			$(INCLUDE_DIR)VirtualMachine.hh	\
			$(INCLUDE_DIR)Debugger.hh	\
			$(INCLUDE_DIR)Script.hh		\
			$(INCLUDE_DIR)Failure.hh	\
			$(INCLUDE_DIR)Example.hh

SRC_DIR		=	./srcs/
SRCS		=	main.cpp			\
			VirtualMachine.cpp Debugger.cpp	\
			Script.cpp RestoreStack.cpp	\
			This.cpp Failure.cpp Example.cpp
SRCS		:=	$(addprefix $(SRC_DIR), $(SRCS))

OBJS_DIR	=	./objs/
OBJS		=	$(SRCS:$(SRC_DIR)%.cpp=%.o)
OBJS		:=	$(notdir $(OBJS))
OBJS		:=	$(addprefix $(OBJS_DIR), $(OBJS))

CXXFLAGS	+=	-Wextra -Wall -Werror -ansi -pedantic-errors -W -g3 -ggdb
CXXFLAGS	+=	-Wunused-macros -Wunused -Wunused-function -Wunused-label
CXXFLAGS	+=	-Wunused-parameter -Wunused-value -Wunused-variable
CXXFLAGS	+=	-Wunused-but-set-parameter -Wunused-but-set-variable

LFLAGS		+=	-llua
DFLAGS		+=


all		:	$(NAME)

$(NAME)		:	$(OBJS) $(INCLUDES_LST)
			@echo -e "Making \033[32m iabomber [OK]\033[0;0m"
			@$(CXX) -o $(NAME) $(OBJS) $(LFLAGS) $(LDFLAGS)
			@echo -e "Flags for iabomber : \033[31m $(CXXFLAGS) \033[0;0m"
			@echo -e "USAGE: ./$(NAME) + luafile \033[0;0m"

clean		:
			@echo -e "Cleaning Programm directory\t\033[32m[OK]\033[0;0m"
			@$(RM) $(SRC_DIR)*~ $(SRC_DIR)\#*\#
			@$(RM) $(OBJS_DIR)*~ $(OBJS_DIR)\#*\# $(OBJS_DIR)*.core $(OBJS_DIR)*.o
			@$(RM) $(INCLUDE_DIR)*~ $(INCLUDE_DIR)\#*\#
			@$(RM) *~ \#*\#

fclean		:	clean
			@$(RM) $(NAME)
			@echo -e "Deleting executable\t\t\033[32m[OK]\033[0;0m"

re		:	fclean all

$(OBJS_DIR)%.o	:	$(SRC_DIR)%.cpp
			@$(CXX) -c $(INCLUDE) $(CXXFLAGS) $(LFLAGS) $(DFLAGS) -o $@ $<
			@echo -e "Compiling for \033[32m iabomber [OK]\033[0;0m" $<

$(OBJS)		:	$(INCLUDES_LST)

.PHONY		:	all re fclean clean

