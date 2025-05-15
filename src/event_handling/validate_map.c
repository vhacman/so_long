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
** Scans the map to validate characters and count special tiles.
** - Accepts only: '0', '1', 'C', 'E', 'P', and '\n'.
** - Increments counters for each collectible, player, and exit.
** - Records the player’s initial (x, y) position.
** - Terminates if any invalid character is found in the map.
**
** Parameters:
** - game: pointer to the game structure containing the map.
** - p_count: pointer to player count (should become 1).
** - e_count: pointer to exit count (should become 1).
** - c_count: pointer to collectible count (should be ≥ 1).
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
** Validates that the map is rectangular and surrounded by wall tiles.
** - Ensures each row has the same length.
** - Checks that the first and last columns in each row are walls ('1').
** - Verifies that the top and bottom rows are fully composed of walls.
** - Exits the program if any of these checks fail.
**
** Parameters:
** - game: pointer to the game structure containing the map.
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
** - Handles full validation of the loaded map structure and content.
**
** Steps:
** 1. Initializes entity counters (players, exits, collectibles).
** 2. Calls check_characters:
**     - Validates all symbols.
**     - Stores player position.
**     - Counts P, E, C.
** 3. Verifies all rows have the same width (redundant check for safety).
** 4. Ensures:
**     - Exactly one player ('P').
**     - Exactly one exit ('E').
**     - At least one collectible ('C').
**     - Map is rectangular and enclosed via check_rectangular_and_walls.
** 5. Saves the number of collectibles in game->collectibles.
**
** If any condition fails, exits the program with a descriptive error.
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
