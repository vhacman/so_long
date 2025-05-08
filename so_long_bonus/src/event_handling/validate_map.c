/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:32:54 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 16:32:54 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Scans the entire map to check for valid characters.
 * - Accepts only allowed symbols: '0' (empty), '1' (wall), 'C' 
 *   (collectible), 'E' (exit), 'P' (player), 'X' (enemy), '\n'.
 * - Increments counters for player (P), exit (E), and collectibles (C).
 * - Records the initial player position in game->player_x/y.
 * - Exits immediately with an error if any invalid character is found.
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
 * Verifies that the map is rectangular and enclosed by walls.
 * - Ensures all rows have the same width as the first one.
 * - First and last character of every row must be wall ('1').
 * - First and last rows must be composed entirely of wall ('1').
 * - Exits with an error if map is not rectangular or not enclosed.
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
 * Validates the structure and content of the entire map.
 * - Calls check_characters() to validate symbols and count required
 *   elements.
 * - Ensures exactly one player, one exit, and at least one collectible.
 * - Verifies rectangular shape by checking all row lengths.
 * - Calls check_rectangular_and_walls() to ensure map enclosure.
 * - Sets total collectible count in game->collectibles.
 * - Exits with specific error if any condition fails.
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
