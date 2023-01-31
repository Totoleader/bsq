# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macote <macote@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/28 12:32:44 by macote            #+#    #+#              #
#    Updated: 2023/01/31 17:28:41 by macote           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

run: compile
	./$(NAME) $(ARGS)
	
runtestmaps: testmaps
	./$(NAME) map map2 map3
compile:
	gcc main.c -o $(NAME)
	
testmaps:
	touch map map2 map3
	./map.pl 50 25 2 > map
	./map.pl 20 10 2 > map2
	./map.pl 5 4 1 > map3

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)
	rm map map2 map3

re: fclean all

