# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmellahi <hmellahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:13:15 by hmellahi          #+#    #+#              #
#    Updated: 2021/06/11 20:59:45 by hmellahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLANG = clang

FLAGS = -lpthread #-g #-fsanitize=address #-Wall -Werror -Wextra

NAME = philo_three

SRC = main.c utils.c messages.c

all: $(NAME)

$(NAME):
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

run:
	$(CLANG) $(FLAGS) ${SRC} -o $(NAME)
	# ./${NAME}  4 410 200 200 3
	./${NAME}  2 0 200 200