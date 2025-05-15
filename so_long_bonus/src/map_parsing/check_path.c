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
** flood_fill:
** - Recursively explores the map starting from (row, col).
** - Marks each reachable tile as visited by overwriting with 'F'.
** - Stops recursion if:
**     - Coordinates are out of bounds.
**     - The tile is a wall ('1') or already visited ('F').
** - Propagates in all four cardinal directions (up, down, left, right).
** - Used to simulate all possible player movements without modifying the
**   original map.
**
** Parameters:
** - map: duplicate of the game map used for flood fill traversal.
** - row: current y-coordinate of the traversal.
** - col: current x-coordinate of the traversal.
** - height: total number of rows in the map.
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
** validate_path:
** - Checks if all collectibles and the exit are reachable from the
**   player's starting position using flood fill.
**
** Steps:
** 1. Duplicates the map using ft_strdup to avoid altering the original.
** 2. Runs flood_fill from the player's initial position to mark reachable tiles.
** 3. Calls check_remaining_elements to verify no 'C' or 'E' remain.
**     - If any are left unvisited, it means they are unreachable.
** 4. Frees the duplicated map via free_map_copy.
** 5. Returns:
**     - 1 if all required tiles are reachable.
**     - 0 if any 'C' or 'E' is unreachable.
**
** If allocation fails at any point, exits the program with an error.
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
