/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:53:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 22:00:34 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Frees a 2D map copy used for pathfinding.
 * - map_copy is an array of strings (char **), each string is a row.
 * - map_height is the number of rows in the map.
 * - Frees each row using free().
 * - Frees the array of pointers after all rows are freed.
 * - Called after flood fill to avoid memory leaks.
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
 * Verifies if all collectibles and exit are reachable.
 * - Iterates through each row and column of map_copy.
 * - If any 'C' (collectible) or 'E' (exit) remains, sets valid to 0.
 * - If all 'C' and 'E' were replaced during flood fill, returns 1.
 * - Used to validate the result of the flood fill algorithm.
 * - map_copy must be a copy of the real map, not the original.
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
			if (map_copy[i][j] == 'C')
				valid = 0;
			j++;
		}
		i++;
	}
	return (valid);
}
