# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hamza <hamza@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/08 16:13:15 by hmellahi          #+#    #+#              #
#    Updated: 2021/06/11 01:16:29 by hamza            ###   ########.fr        #
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
	./${NAME}  4  510 200 200