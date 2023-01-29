/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:26:52 by macote            #+#    #+#             */
/*   Updated: 2023/01/28 16:42:47 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

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
int get_lenght(char *map)
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

int get_height(char *map)
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