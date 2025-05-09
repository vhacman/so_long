/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:32:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 16:32:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Validates all characters in the map and counts special tiles.
 * - Accepts only: '0' (empty), '1' (wall), 'C' (collectible),
 *   'E' (exit), 'P' (player), and '\n' (newline).
 * - Increments counters for player, exit, and collectible tiles.
 * - Saves the player's starting coordinates to game->player_x/y.
 * - Exits immediately with an error if an invalid character is found.
 */
void	check_characters(t_game *game, int *p_count, int *e_count,
							int *c_count)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_char(game->map[i][j]) && game->map[i][j] != '\n')
				exit_with_error("Error\nInvalid character in map\n", game, 1);
			if (game->map[i][j] == 'P')
			{
				game->player_y = i;
				game->player_x = j;
				(*p_count)++;
			}
			if (game->map[i][j] == 'E')
				(*e_count)++;
			if (game->map[i][j] == 'C')
				(*c_count)++;
			j++;
		}
		i++;
	}
}

/*
 * Ensures the map is rectangular and completely enclosed by walls.
 * - Checks that all rows have the same length (rectangularity).
 * - Validates that the first and last columns contain only '1'.
 * - Validates that the first and last rows are filled with '1'.
 * - Exits with an error if any wall condition is violated.
 */
void	check_rectangular_and_walls(t_game *game)
{
	int	width;
	int	i;
	int	j;

	width = ft_strlen(game->map[0]);
	i = 0;
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != width)
			exit_with_error("Error\nMap is not rectangular\n", game, 1);
		if (game->map[i][0] != '1' || game->map[i][width - 1] != '1')
			exit_with_error("Error\nMap not enclosed(verical).\n", game, 1);
		i++;
	}
	j = 0;
	while (j < width)
	{
		if (game->map[0][j] != '1' || game->map[i - 1][j] != '1')
			exit_with_error("Error\nMap not enclosed(horizontal)\n", game, 1);
		j++;
	}
}

/*
 * Validates the structure and required content of the map.
 * - Calls check_characters() to ensure symbols are valid and counted.
 * - Confirms each row matches game->map_width to enforce rectangularity.
 * - Requires exactly 1 player ('P'), 1 exit ('E'),
 *   and at least 1 collectible ('C').
 * - Calls check_rectangular_and_walls() to ensure boundary walls.
 * - Stores the collectible count in game->collectibles for gameplay tracking.
 * - Exits if any condition is violated.
 */
void	validate_map(t_game *game)
{
	int	p_count;
	int	e_count;
	int	c_count;
	int	i;

	p_count = 0;
	e_count = 0;
	c_count = 0;
	i = 0;
	check_characters(game, &p_count, &e_count, &c_count);
	while (game->map[i])
	{
		if ((int)ft_strlen(game->map[i]) != game->map_width)
			exit_with_error("Error\nMap is not rectangular\n", game, 1);
		i++;
	}
	if (p_count != 1)
		exit_with_error("Error\nMap must contain 1 P\n", game, 1);
	if (e_count != 1)
		exit_with_error("Error\nMap must contain 1 E\n", game, 1);
	if (c_count < 1)
		exit_with_error("Error\nMap must contain at least 1 C\n", game, 1);
	check_rectangular_and_walls(game);
	game->collectibles = c_count;
}
