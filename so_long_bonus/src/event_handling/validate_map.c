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
 ** check_characters:
 ** Scans entire map for allowed characters only.
 ** Allowed: '0', '1', 'C', 'E', 'P', 'X', '\n'.
 ** Counts number of players (P), exits (E), collectibles (C).
 ** Stores player initial coordinates in game->player_x/y.
 ** Exits with error if any invalid character found.
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
 ** check_rectangular_and_walls:
 ** Ensures map is rectangular: all rows same width.
 ** Checks first and last character of each row are '1' (walls).
 ** Checks top and bottom rows are fully '1'.
 ** Exits with error if shape or enclosure invalid.
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
 ** validate_map:
 ** Calls check_characters to validate symbols and count elements.
 ** Confirms exactly one player and exit, at least one collectible.
 ** Validates all rows match expected width (rectangular).
 ** Calls check_rectangular_and_walls to verify map enclosure.
 ** Stores total collectibles count in game->collectibles.
 ** Exits with specific errors on any validation failure.
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
