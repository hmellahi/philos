# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:13:15 by hmellahi          #+#    #+#              #
#    Updated: 2021/10/05 18:16:09 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = gcc

FLAGS = -lpthread -Wall -Werror -Wextra

NAME = philo

SRC = main.c ../utils/utils.c messages.c init.c life_circle.c

all: $(NAME)

$(NAME): $(SRC)
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all