##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile REGNAULT Steeven
##

.DEFAULT_GOAL := all

## ZAPPY SERVER ##

SERVER_NAME	=	zappy_server

SERVER_DIR	=	./src/server

SERVER_SRCS	=	$(SERVER_DIR)/main.c					\
			$(SERVER_DIR)/tools/help.c				\
			$(SERVER_DIR)/tools/array.c				\
			$(SERVER_DIR)/tools/string.c				\
			$(SERVER_DIR)/tools/number.c				\
			$(SERVER_DIR)/tools/math.c				\
			$(SERVER_DIR)/core/zappy.c				\
			$(SERVER_DIR)/core/zappy_loop.c				\
			$(SERVER_DIR)/core/update.c				\
			$(SERVER_DIR)/core/death.c				\
			$(SERVER_DIR)/core/map/generate.c			\
			$(SERVER_DIR)/core/map/food.c				\
			$(SERVER_DIR)/parsing/argument.c			\
			$(SERVER_DIR)/parsing/parse_name.c			\
			$(SERVER_DIR)/parsing/parse_int.c			\
			$(SERVER_DIR)/init/default_values.c			\
			$(SERVER_DIR)/init/core.c				\
			$(SERVER_DIR)/init/socket.c				\
			$(SERVER_DIR)/client/client.c				\
			$(SERVER_DIR)/command/get_command.c			\
			$(SERVER_DIR)/command/execute_command.c			\
			$(SERVER_DIR)/command/team.c				\
			$(SERVER_DIR)/command/time.c				\
			$(SERVER_DIR)/command/player.c				\
			$(SERVER_DIR)/command/incant.c				\
			$(SERVER_DIR)/command/command_parser.c			\
			$(SERVER_DIR)/command/commands/graphic.c		\
			$(SERVER_DIR)/command/commands/direction.c		\
			$(SERVER_DIR)/command/commands/graphic/msz.c		\
			$(SERVER_DIR)/command/commands/graphic/bct.c		\
			$(SERVER_DIR)/command/commands/graphic/mct.c		\
			$(SERVER_DIR)/command/commands/graphic/tna.c		\
			$(SERVER_DIR)/command/commands/graphic/sgt.c		\
			$(SERVER_DIR)/command/commands/graphic/sst.c		\
			$(SERVER_DIR)/command/commands/graphic/ppo.c		\
			$(SERVER_DIR)/command/commands/graphic/plv.c		\
			$(SERVER_DIR)/command/commands/graphic/pin.c		\
			$(SERVER_DIR)/command/commands/player/inventory.c	\
			$(SERVER_DIR)/command/commands/player/broadcast.c	\
			$(SERVER_DIR)/command/commands/player/left.c		\
			$(SERVER_DIR)/command/commands/player/right.c		\
			$(SERVER_DIR)/command/commands/player/forward.c		\
			$(SERVER_DIR)/command/commands/player/look.c		\
			$(SERVER_DIR)/command/commands/player/look_content.c	\
			$(SERVER_DIR)/command/commands/player/connect_nbr.c	\
			$(SERVER_DIR)/command/commands/player/take.c		\
			$(SERVER_DIR)/command/commands/player/set.c		\
			$(SERVER_DIR)/command/commands/player/eject.c		\
			$(SERVER_DIR)/command/commands/player/fork.c		\
			$(SERVER_DIR)/command/commands/player/incantation.c	\

SERVER_OBJS	=	$(SERVER_SRCS:.c=.o)

CC		=	cc

server_include	=	-I./include

CFLAGS		+=	-Wextra -Wall -W $(server_include)

RM		=	@rm -f

$(SERVER_NAME)	:	$(SERVER_OBJS)
			@$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) -lm
.PHONY		:	$(SERVER_NAME)

clean_server	:
			@$(RM) $(SERVER_OBJS)
.PHONY		:	clean_server

fclean_server	:	clean_server
			@$(RM) $(SERVER_NAME)
.PHONY		:	fclean_server

re_server	:	fclean_server
			@$(MAKE) $(SERVER_NAME)
.PHONY		:	re_server

tests_run	:
			@$(MAKE) -C ./tests
			./tests/unit-tests
.PHONY		:	tests_run

tests_re	:
			@$(MAKE) re -C ./tests
			./tests/unit-tests
.PHONY		:	tests_re

tests_clean	:
			@$(MAKE) fclean -C ./tests
.PHONY		:	tests_clean

## ZAPPY GRAPHICAL ##

GRAPHIC_NAME	=	zappy_graphical

GRAPHIC_DIR	=	./src/graphical

GRAPHIC_SRCS	=	$(GRAPHIC_DIR)/main.cpp					\
			$(GRAPHIC_DIR)/Network/TCPClient.cpp			\
			$(GRAPHIC_DIR)/ZappyGraphic/ZappyGraphic.cpp		\
			$(GRAPHIC_DIR)/Command/cmdFunction.cpp			\
			$(GRAPHIC_DIR)/Command/CommandHandler.cpp		\

GRAPHIC_OBJS	=	$(GRAPHIC_SRCS:.cpp=.o)

CXX		=	g++

graphic_include	=	-I./src/graphical/

CXXFLAGS	+=	-std=c++14 -Wextra -Wall -W $(graphic_include)

GRAPHIC_LIBS	=	-lsfml-graphics -lsfml-window -lsfml-system -lpthread

$(GRAPHIC_NAME)	:	$(GRAPHIC_OBJS)
			@$(CXX) -o $(GRAPHIC_NAME) $(GRAPHIC_OBJS) $(GRAPHIC_LIBS)
.PHONY		:	$(GRAPHIC_NAME)

clean_graphical	:
			@$(RM) $(GRAPHIC_OBJS)
.PHONY		:	clean_graphical

fclean_graphical:	clean_graphical
			@$(RM) $(GRAPHIC_NAME)
.PHONY		:	fclean_graphical

re_graphical	:	fclean_graphical
			@$(MAKE) $(GRAPHIC_NAME)
.PHONY		:	re_graphical

## ZAPPY AI ##

AI_NAME		=	zappy_ai

$(AI_NAME)	:
			echo '#!/bin/bash' > $(AI_NAME)
			echo './src/ai/zappy_ai $$@' >> $(AI_NAME)
			chmod +x $(AI_NAME)
.PHONY		:	$(AI_NAME)

fclean_ai	:
			@$(RM) $(AI_NAME)
.PHONY		:	$(fclean_ai)

## GLOBAL RULES ##

all		:
			@$(MAKE) -s $(SERVER_NAME)
			@$(MAKE) -s $(GRAPHIC_NAME)
			@$(MAKE) -s $(AI_NAME)
.PHONY		:	all

clean		:	clean_server clean_graphical
.PHONY		:	clean

fclean		:	fclean_server fclean_graphical fclean_ai
.PHONY		:	fclean

re		:	re_server re_graphical $(AI_NAME)
.PHONY		:	re
