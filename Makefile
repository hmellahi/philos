# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:13:15 by hmellahi          #+#    #+#              #
#    Updated: 2021/06/08 21:20:30 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang

FLAGS = -g -fsanitize=address #-Wall -Werror -Wextra

NAME = philo_0

SRC = main.c sf_malloc.c utils.c messages.c

all: $(NAME)

$(NAME):
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

run:
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)
	./philo_0 5  100 500 500 3