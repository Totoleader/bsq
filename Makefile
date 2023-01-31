# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macote <macote@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 12:32:44 by macote            #+#    #+#              #
#    Updated: 2023/01/31 15:16:46 by macote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

run: compile
	./$(NAME) $(ARGS)

compile:
	gcc main.c -o $(NAME)
	
testmaps:
	./map.pl 25 25 2 > map
	./map.pl 25 25 2 > map2
	./map.pl 25 25 2 > map3

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

