/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loading_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:28:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 11:28:24 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Cleans up each row of the map by removing line-ending characters.
 * - Iterates through all rows of game->map.
 * - Removes trailing '\n' or '\r' characters by replacing them with '\0'.
 * - Ensures correct map parsing and prevents layout issues.
 */
void	clean_map(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (game->map[i])
	{
		len = ft_strlen(game->map[i]);
		while (len > 0 && (game->map[i][len - 1] == '\n'
			|| game->map[i][len - 1] == '\r'))
		{
			game->map[i][len - 1] = '\0';
			len--;
		}
		i++;
	}
}

/*
 * Prints an error message to stderr and exits the program.
 * - If flag == 1, calls cleanup() to free game resources.
 * - Uses ft_putstr_fd() for output and exit(EXIT_FAILURE) to abort.
 * - Ensures clean termination in case of errors.
 */
void	exit_with_error(char *msg, t_game *game, int flag)
{
	ft_putstr_fd(msg, 2);
	if (flag == 1)
		cleanup (game);
	exit (EXIT_FAILURE);
}

/*
 * Verifies if a character is valid within the map context.
 * - Allowed characters: 
 *   '0' = empty, '1' = wall, 'C' = collectible,
 *   'E' = exit, 'P' = player, 'X' = enemy.
 * - Returns 1 for valid characters, 0 for invalid.
 */
int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C'
		|| c == 'E' || c == 'P' || c == 'X');
}
