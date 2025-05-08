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
 * Frees the memory used by a map copy.
 * - Iterates over all rows and frees each string.
 * - Frees the map_copy array itself.
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
 * Checks if any unreachable collectibles ('C') or exit ('E') remain.
 * - Iterates through the map copy.
 * - Returns 1 if all 'C' and 'E' have been visited (i.e., replaced).
 * - Returns 0 if any 'C' or 'E' remains.
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
