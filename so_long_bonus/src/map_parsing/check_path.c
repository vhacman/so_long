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

#include "so_long_bonus.h"

/* 
 * Performs recursive flood fill starting from (row, col).
 * - Replaces walkable tiles with 'F' to mark them as visited.
 * - Stops if out of bounds, hits a wall ('1'), or already visited ('F').
 * - Recursively visits all 4 directions.
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
 * Validates if all collectibles and the exit are reachable from player.
 * - Duplicates the map to preserve original state.
 * - Runs flood_fill from the player's starting position.
 * - Uses check_remaining_elements() to detect unreachable 'C' or 'E'.
 * - Frees the copied map.
 * - Returns 1 if all targets are reachable, 0 otherwise.
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
