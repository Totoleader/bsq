/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:11:04 by macote            #+#    #+#             */
/*   Updated: 2023/01/29 15:50:12 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "helper.h"


//ouvre le fichier qui contient la map et renvoie une string qui contient la map
char *raw_map(void)
{
	int fd;                                             // file descriptor
	char *map;                                          // where the map will be copied
	
	map = (char *)malloc(sizeof(char) * 10000000);		// allocate memory for the map to be copied
	fd = open("map", O_RDWR);                           // open the file
	
	read(fd, map, sizeof(char) * 10000000);             // read the file
	close(fd);
	
	return (map);
}

//prend raw_map et enleve les deux premieres lignes d'information
char *raw_map_cleaned(char *map)
{
	int nb_of_newlines;
	int i;
	
	nb_of_newlines = 0;
	i = 0;
	
	//trouve l'endroit après le deuxièmme \n
	while (nb_of_newlines < 2)
	{
		if (map[i +1] == '\n')
		{
			nb_of_newlines++;
		}
		i++;
	}
	//retourne l'endroit après le deuxièmme \n
	map = &map[i + 1];
	return (map);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                        OPERATIONS SUR MAP DE BASE EN HAUT                             /////////
/////////                                                                                       /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////



//returns density of map from raw map
int get_density(char *map)
{
	int i;
	int nbr_of_space;
	int resultat;
	
	i = 0;
	nbr_of_space = 0;
	resultat = 0;
	while (nbr_of_space != 2)
	{
		if (map[i] == ' ')
			nbr_of_space++;
		i++;
	}
	
	while (map[i] >= '0' && map[i] <= '9')
	{
		resultat *= 10;
		resultat += (map[i] - 48);
		i++;	
	}
	return(resultat);
}

//returns lenght of map from raw map
int get_lenght(char *map)
{
	int i;
	int resultat;
	
	i = 0;
	resultat = 0;
	while (map[i] != ' ')
	{
		resultat *= 10;
		resultat += (map[i] - 48);
		i++;	
	}
	return(resultat);
}

//returns height of map from raw map
int get_height(char *map)
{
	int i;
	int nbr_of_space;
	int resultat;
	
	i = 0;
	nbr_of_space = 0;
	resultat = 0;
	while (nbr_of_space != 1)
	{
		if (map[i] == ' ')
			nbr_of_space++;
		i++;
	}
	
	while (map[i] != ' ')
	{
		resultat *= 10;
		resultat += (map[i] - 48);
		i++;	
	}
	return(resultat);
}

//returns the number of char in the map from get_lenght() and get_height()
int get_char_lenght(char* map)
{
	int char_lenght;
	
	char_lenght = get_height(map) * get_lenght(map);
	return (char_lenght);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                              HELPER EN HAUT                                           /////////
/////////                                                                                       /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////





//prend raw_map_cleaned en parametre et alloue de la memoire pour le stocker en tableau
char **map_canvas(char *map)
{
	char **array_map;
	int i;
	
	i = 0;
	
	//alloue le nb de ligne
	array_map = (char**)malloc(sizeof(char *) * get_height(raw_map()));
	
	//alloue le nb de caractere par ligne
	while (i < get_height(raw_map()))
	{
		array_map[i] = malloc(sizeof(char) * get_lenght(raw_map()));
		i++;
	}
	//libere la memoir allouée a raw_map
	free(raw_map());
	return (array_map);
}


// returns the map in a organised in a char** with [i]rows and j[colums]
char **map_filled(char **map_canvas, char *raw_map_clean)
{
	int i;
	int j;
	int k;
	
	i = 0;
	j = 0;
	k = 0;
	while (raw_map_clean[k])
	{
		//si c'est pas \n copie
		if (raw_map_clean[k] != '\n')
		{
			map_canvas[i][j] = raw_map_clean[k];
			j++;
		}
		//si c'est \n ne copie pas et commence une autre ligne
		else
		{
			j = 0;
			i++;
		}
		//incrémente k dans tout les cas
		k++;
	}
	return (map_canvas);
}

int main(int argc, char **argv)
{
	int i;
	char **canvas_map;
	char *cleaned_map;
	char **filled_map;
	
	canvas_map = map_canvas(raw_map_cleaned(raw_map()));
	cleaned_map = raw_map_cleaned(raw_map());
	
	filled_map = map_filled(canvas_map, cleaned_map);
	
	i = 0;
	while (i < get_height(raw_map()))
	{
		printf("%s", filled_map[i]);
		printf("\n");
		i++;
	}

	return (0);
}
