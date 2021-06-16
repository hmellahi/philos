# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:13:15 by hmellahi          #+#    #+#              #
#    Updated: 2021/06/16 16:24:46 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang

FLAGS = -lpthread -Wall -Werror -Wextra #-g #-fsanitize=address #-Wall -Werror -Wextra

NAME = philo_one

SRC = main.c ../utils/utils.c messages.c init.c life_circle.c

all: $(NAME)

$(NAME):
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

run:
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)
	./${NAME} 4  0 200 200