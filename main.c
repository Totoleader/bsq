/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 12:11:04 by macote            #+#    #+#             */
/*   Updated: 2023/01/31 16:47:20 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "helper.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                        OPERATIONS SUR MAP DE BASE EN HAUT                             /////////
/////////                                        |                                              /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////


//ouvre le fichier qui contient la map et renvoie une string qui contient la map
char *raw_map(char *argv)
{
	int fd;                                             // file descriptor
	char *map;                                          // where the map will be copied
	
	map = (char *)malloc(sizeof(char) * 10000000);		// allocate memory for the map to be copied
	fd = open(argv, O_RDWR);                           // open the file
	
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
	
	//trouve l'endroit après le premier \n
	while (nb_of_newlines < 1)
	{
		if (map[i +1] == '\n')
		{
			nb_of_newlines++;
		}
		i++;
	}
	//retourne l'endroit après le premier \n
	map = &map[i + 1];
	return (map);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                             GENERIC HELPERS  			                                /////////
/////////                                   |                                                   /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void error(void)
{
	write(STDERR_FILENO, "map error\n", 10);
	//exit(0);
}

void check_identical_error(char dot,char o, char x)
{
	//check les double
	if ((dot == o) || (dot == x) || (o == x))
	{
	 error();
	}
	//check si c'est imnprimmable ou il en manque un
	if ((dot < ' ') || (x < ' ') || (o < ' ')
		||(dot > '~') || (x > '~') || (o > '~'))
	{
	 error();
	}
}

char plein_vide_obs(char *map, char car)
{
	int i;
	int j;
	int endline;
	char vide_obs_plein[3];

	i = 0;
	j = 2;
	while (map[i + 1] != '\n')
	{
		i++;
	}
	endline = i;
	while (i > (endline - 3))
	{
		vide_obs_plein[j] = map[i];
		j--;
		i--;
	}
	check_identical_error(vide_obs_plein[0], vide_obs_plein[1], vide_obs_plein[2]);
	if (car == 'o')
		return (vide_obs_plein[1]);
	if (car == 'x')
		return (vide_obs_plein[2]);
	else
		return (vide_obs_plein[0]);
}


int    get_height(char *map)
{
    int x;
    int xx;
    int y;
    int cmp;
    xx = 0;
    x = 0;
    y = 0;
    cmp = 0;
    while (map[xx] != '\n')
    {
        xx++;
    }
    while (map[xx] != '\0')
    {
        xx++;
        x = 0;
        while (map[xx] != '\n')
        {
            x++;
            xx++;
            if (map[xx] == '\0')
                break ;
        }
        cmp = x;
        y++;
    }
    return (y - 1);
}
int get_lenght(char *map)
{
    int x;
    int xx;
    int y;
    int cmp;
    xx = 0;
    x = 0;
    y = 0;
    cmp = 0;
    while (map[xx] != '\n')
    {
        xx++;
    }
    while (map[xx + 1] != '\0')
    {
        xx++;
        x = 0;
        while ((map[xx] != '\n' && map[xx] != '\0') || map[xx] == '\0')
        {
            x++;
            xx++;
            if (map[xx] == '\0')
                break ;
        }
        if ((y != 0 && cmp != x) || (y == 1 && x <= 0))
            error();
        cmp = x;
        y++;
    }
    return (cmp);
}
// //returns lenght of map from raw map
// int get_lenght(char *map)
// {
// 	// int i;
// 	// int resultat;
	
// 	// i = 0;
// 	// resultat = 0;
// 	// while (map[i] != ' ')
// 	// {
// 	// 	resultat *= 10;
// 	// 	resultat += (map[i] - 48);
// 	// 	i++;	
// 	// }
// 	return(25);
// }

//returns height of map from raw map
// int get_height(char *map)
// {
// 	// int i;
// 	// int nbr_of_space;
// 	// int resultat;
	
// 	// i = 0;
// 	// nbr_of_space = 0;
// 	// resultat = 0;
// 	// while (nbr_of_space != 1)
// 	// {
// 	// 	if (map[i] == ' ')
// 	// 		nbr_of_space++;
// 	// 	i++;
// 	// }
	
// 	// while (map[i] != ' ')
// 	// {
// 	// 	resultat *= 10;
// 	// 	resultat += (map[i] - 48);
// 	// 	i++;	
// 	// }
// 	return(25);
// }

//returns the number of char in the map from get_lenght() and get_height()
int get_char_lenght(char* map)
{
	int char_lenght;
	
	char_lenght = get_height(map) * get_lenght(map);
	return (char_lenght);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                              MAP ORGANISÉE                                            /////////
/////////                                   |                                                   /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////





//prend raw_map_cleaned en parametre et alloue de la memoire pour le stocker en tableau
char **map_canvas(char *map, char *argv)
{
	char **array_map;
	int i;
	
	i = 0;
	
	//alloue le nb de ligne
	array_map = (char**)malloc(sizeof(char *) * get_height(raw_map(argv)));
	
	//alloue le nb de caractere par ligne
	while (i < get_height(raw_map(argv)))
	{
		array_map[i] = malloc(sizeof(char) * get_lenght(raw_map(argv)));
		i++;
	}
	//libere la memoir allouée a raw_map
	free(raw_map(argv));
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



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                              ALGO HELPERS                                             /////////
/////////                                   |                                                   /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////



char **o_to_0(char **map, char *argv)
{
    int j;
    int i;
    i = 0;
    while (i < (get_height(raw_map(argv))))
    {
        j = 0;
        while (j < (get_lenght(raw_map(argv))))
        {
            if (map[i][j] == plein_vide_obs(raw_map(argv), 'o'))
                map[i][j] = '0';
            j++;
        }
        i++;
    }
    return (map);
}


char algo_compare(char gauche, char haut, char haut_gauche)
{   
    char min;

    if (gauche < haut)
        min = gauche;
    else                
        min = haut;
    if (haut_gauche < min)
        min = haut_gauche;

        return(min);
}


char **first_i_j(char **dest, char *argv)
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (j < (get_lenght(raw_map(argv))))
    {
        {
            if (dest[i][j] != '0')
                dest[i][j] = '1';
        }
        j++;
    }
    j = 0;
    while (i < (get_height(raw_map(argv))))
    {
        if (dest[i][j] != '0')
            dest[i][j] = '1';
        i++;
    }
    return (dest);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////                                                                                       /////////
/////////                               MAIN ALGO                                               /////////
/////////                                   |                                                   /////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

char **main_algo(char **map, char *argv)
{
    int i;
    int j;
    char min;

    i = 1;
    while (i < get_height(raw_map(argv)))
    {
        j = 1;
        while (j < get_lenght(raw_map(argv)))
        {	
			if (map[i][j] != '0')
			{
				min = algo_compare(map[i][j - 1], map[i - 1][j], map[i - 1][j - 1]);
            	map[i][j] = min + 1;
			}	
            j++;
        }
        i++;
    }
    return(map);
}

//methode qui cherche l'adresse du max(**map)
char *find_max_adress(char **map, char *argv)
{
	int i;
    int j;
	char max;
	char *max_adress;
	
    i = 1;
	max = '0';
    while (i < get_height(raw_map(argv)))
    {
        j = 1;
        while (j < get_lenght(raw_map(argv)))
        {	
			if (map[i][j] > max)
			{
				max = map[i][j];
				max_adress = &map[i][j];
			}
            j++;
        }
        i++;
    }
    return(max_adress);
}


char** put_x_on_map(char **map, int i_de_base, int j_de_base, char max, char *argv)
{
	char max_i;
	char max_j;
	int i;
	int j;

	i = i_de_base;
	max_i = max;
	max_j = max;
    while (max_i > '0')
    {
		max_j = max;
		j = j_de_base;
        while (max_j > '0')
        {	
			map[i][j] = plein_vide_obs(raw_map(argv), 'x');
			j--;
			max_j--;
        }
		i--;
		max_i--;
    }
	return(map);
}


//methode qui chherche l'adresse du max dans la map(**map, adresse_max)
char** put_all_x_on_map(char **map, char* adress_max, char *argv)
{
	int i;
    int j;
	
    i = 0;
    while (i < get_height(raw_map(argv)))
    {
        j = 0;
        while (j < get_lenght(raw_map(argv)))
        {	
			if (&map[i][j] == adress_max)
			{
				put_x_on_map(map, i, j, map[i][j], argv);
			}
			else if (map[i][j] == '0')
			{
				map[i][j] = plein_vide_obs(raw_map(argv), 'o');
			}
			else
			{
				map[i][j] = plein_vide_obs(raw_map(argv), '.');
			}
			
            j++;
        }
        i++;
    }
	return(map);
}

void print_result(char *argv)
{
	int i;
	char **canvas_map;
	char *cleaned_map;
	char **filled_map;
	char **algo_prep_map;
	char **algo_result_map;
	char **result;
	
	canvas_map = map_canvas(raw_map_cleaned(raw_map(argv)), argv);
	cleaned_map = raw_map_cleaned(raw_map(argv));
	filled_map = map_filled(canvas_map, cleaned_map);
	algo_prep_map = first_i_j(o_to_0(filled_map, argv), argv);
	algo_result_map = main_algo(algo_prep_map, argv);
	result = put_all_x_on_map(algo_result_map, find_max_adress(algo_result_map, argv), argv);
	
	i = 0;
	while (i < get_height(raw_map(argv)))
	{
		printf("%s", result[i]);
		printf("\n");
		i++;
	}

	write(1, "\n", 1);
}

void print_all_results(int argc, char **argv)
{
	int i;

	i = 1;
	while (argc > 1)
	{
		print_result(argv[i]);
		i++;
		argc--;
	}
	
}

int main(int argc, char **argv)
{
	print_all_results(argc, argv);
	return (0);
}
