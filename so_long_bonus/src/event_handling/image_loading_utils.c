/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loading_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:28:24 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 11:28:24 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Removes newline and carriage return characters from map rows.
 * - Ensures clean parsing and rendering by eliminating trailing
 *   control characters.
 * - Modifies each row in-place by replacing '\n' or '\r' with '\0'.
 * - Prevents logical errors in map validation and display.
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
 * Prints an error message and terminates the program.
 * - Displays the message to stderr using ft_putstr_fd().
 * - If flag is 1, calls cleanup() to free all resources.
 * - Exits with status EXIT_FAILURE to indicate abnormal termination.
 */
void	exit_with_error(char *msg, t_game *game, int flag)
{
	ft_putstr_fd(msg, 2);
	if (flag == 1)
		cleanup (game);
	exit (EXIT_FAILURE);
}

/*
 * Validates characters used in the map file.
 * - Returns 1 if the character is allowed in the map layout.
 * - Allowed characters: '0' (empty), '1' (wall), 'C' (collectible),
 *   'E' (exit), 'P' (player), 'X' (enemy).
 * - Returns 0 for any invalid character.
 */
int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C'
		|| c == 'E' || c == 'P' || c == 'X');
}
