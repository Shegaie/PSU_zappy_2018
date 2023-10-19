##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile REGNAULT Steeven,
##

NAME		=	unit-tests

PROJECT_DIR	= 	./../src/server

TEST_DIR	=	./src

SRCS		=	$(PROJECT_DIR)/parsing/argument.c			\
			$(PROJECT_DIR)/parsing/parse_int.c			\
			$(PROJECT_DIR)/parsing/parse_name.c			\
			$(PROJECT_DIR)/init/default_values.c			\
			$(PROJECT_DIR)/init/socket.c				\
			$(PROJECT_DIR)/tools/array.c				\
			$(PROJECT_DIR)/tools/help.c				\
			$(PROJECT_DIR)/tools/number.c				\
			$(PROJECT_DIR)/tools/math.c				\
			$(PROJECT_DIR)/client/client.c				\
			$(PROJECT_DIR)/core/map/generate.c			\
			$(PROJECT_DIR)/core/map/food.c				\
			$(PROJECT_DIR)/command/commands/graphic/bct.c		\
			$(PROJECT_DIR)/command/command_parser.c			\
			$(PROJECT_DIR)/command/commands/direction.c		\
			$(TEST_DIR)/core/map/generate.c				\
			$(TEST_DIR)/tools/number.c				\
			$(TEST_DIR)/client/client.c				\
			$(TEST_DIR)/redirect.c					\
			$(TEST_DIR)/parsing/parsing_name.c			\
			$(TEST_DIR)/init/init.c					\
			$(TEST_DIR)/init/socket_init.c				\
			$(TEST_DIR)/tools/tools.c				\
			$(TEST_DIR)/tools/math.c				\
			$(TEST_DIR)/parsing/parsing_global.c			\
			$(TEST_DIR)/parsing/parsing_int.c			\
			$(TEST_DIR)/tools/tools_array.c				\
			$(TEST_DIR)/command/direction.c				\
			$(TEST_DIR)/command/direction_points.c			\

OBJS		=	$(SRCS:.c=.o)

GCDA		=	$(SRCS:.c=.gcda)

GCNO		=	$(SRCS:.c=.gcno)

CC		=	gcc

CFLAGS		+=	-Wextra -Wall -W -I./../include -I./include --coverage -lcriterion

RM		=	@rm -f

all		:
			@make $(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -lm

clean		:
			$(RM) $(GCDA) $(GCNO) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
