/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:44:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 11:44:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Performs a recursive flood fill to simulate player movement.
 * - Starts at (row, col), which is the player's position.
 * - Recursively marks all reachable tiles with 'F'.
 * - Stops if out of bounds, on a wall ('1'), or on an already
 *   visited tile ('F').
 * - This does not modify the original map, only the temporary copy.
 * - The result is used to verify reachability of 'C' and 'E' tiles.
 */
static void	flood_fill(char **map, int row, int col, int height)
{
	if (row < 0 || col < 0 || row >= height || col >= (int)ft_strlen(map[0]))
		return ;
	if (map[row][col] == '1' || map[row][col] == 'F')
		return ;
	map[row][col] = 'F';
	flood_fill(map, row + 1, col, height);
	flood_fill(map, row - 1, col, height);
	flood_fill(map, row, col + 1, height);
	flood_fill(map, row, col - 1, height);
}

/*
 * Validates that all collectibles and exit can be reached.
 * - Allocates a temporary copy of the original map.
 * - Duplicates each line of the map with ft_strdup().
 * - Calls flood_fill() starting from the player's position.
 * - Uses check_remaining_elements() to see if all 'C' and 'E'
 *   were reached (converted to 'F').
 * - Frees the map copy using free_map_copy().
 * - Returns 1 if the map is valid, 0 if any target is unreachable.
 * - Exits if memory allocation fails during duplication.
 */
int	validate_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		valid;

	map_copy = malloc(sizeof(char *) * (game->map_height +1));
	if (!map_copy)
		exit_with_error("allocation failed path validation\n", game, 1);
	i = 0;
	while (i < game->map_height)
	{
		map_copy[i] = ft_strdup(game->map[i]);
		if (!map_copy)
			exit_with_error("Memory allocation failed\n", game, 1);
		i++;
	}
	map_copy[i] = NULL;
	flood_fill(map_copy, game->player_y, game->player_x, game->map_height);
	valid = check_remaining_elements(map_copy, game->map_height);
	free_map_copy(map_copy, game->map_height);
	return (valid);
}
