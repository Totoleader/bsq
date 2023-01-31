# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macote <macote@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 12:32:44 by macote            #+#    #+#              #
#    Updated: 2023/01/31 10:58:16 by macote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq
SRC = main.c
H ?= 25
L ?= 25
D ?= 5
MAP = ./map.pl $(L) $(H) $(D)
DIMENSIONS = echo $(L) $(H) $(D)

run: $(NAME)
	./$(NAME)

$(NAME): get_map
	gcc -o $(NAME) $(SRC)

get_map:
	$(MAP) > map

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

