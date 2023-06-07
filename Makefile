# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 18:35:35 by fpereira          #+#    #+#              #
#    Updated: 2023/03/15 16:50:42 by fpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -g -fsanitize=thread
RM			=	rm -f
MKD			=	mkdir
INC			=	-I ./includes

NAME		=	philo

OBJ_PATH	=	./obj
SRCS		=	$(SRC_PATH)/all_ate.c $(SRC_PATH)/main.c $(SRC_PATH)/param_parse.c \
					$(SRC_PATH)/prints_exits.c $(SRC_PATH)/utils.c
OBJ_SRCS	= 	$(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,$(SRCS))

SRC_PATH	=	./srcs

all: $(NAME)

$(NAME) : $(OBJ_SRCS)
	$(CC) $(CFLAGS) $(OBJ_SRCS) $(INC) -o $(NAME) -pthread

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ_PATH)/*.o

fclean: clean
		$(RM) $(NAME)
		if [ -d $(OBJ_PATH) ]; then rmdir $(OBJ_PATH); fi

re: fclean all