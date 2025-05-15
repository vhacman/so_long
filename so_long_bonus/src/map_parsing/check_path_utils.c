/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:53:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 11:53:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** free_map_copy:
** - Frees all memory allocated for a duplicated map.
** - Iterates through each row (string) in map_copy and frees it.
** - After all rows are freed, frees the map_copy pointer itself.
** - Used in validate_path to clean up after flood fill simulation.
**
** Parameters:
** - map_copy: 2D array of strings representing the duplicated map.
** - map_height: number of rows in the map.
*/
void	free_map_copy(char **map_copy, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

/*
** check_remaining_elements:
** - Scans the flood-filled map copy to detect unreachable objectives.
** - Iterates through each tile of the map.
** - If any collectible ('C') or exit ('E') is found, sets valid = 0.
**   → This means the tile was not reached by flood fill.
** - Returns 1 if all collectibles and the exit are reachable.
** - Returns 0 if any of them remain unreachable.
**
** Parameters:
** - map_copy: pointer to the flood-filled map.
** - map_height: number of rows in the map.
*/
int	check_remaining_elements(char **map_copy, int map_height)
{
	int	i;
	int	j;
	int	valid;

	valid = 1;
	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == 'C' || map_copy[i][j] == 'E')
				valid = 0;
			j++;
		}
		i++;
	}
	return (valid);
}
