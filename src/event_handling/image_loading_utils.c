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
** clean_map:
** - Iterates over all lines in game->map.
** - Removes any trailing '\n' or '\r' characters by replacing them
**   with '\0'.
** - Ensures uniform string formatting across platforms.
** - Prevents map parsing errors during validation and rendering.
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
** Prints an error message to stderr and terminates the program.
** - If `flag` is set to 1, invokes cleanup() to free game resources.
** - Uses ft_putstr_fd() to print the error message.
** - Exits with status code EXIT_FAILURE (1).
**
** Parameters:
** - msg: error message to be printed.
** - game: pointer to the game structure (used by cleanup if needed).
** - flag: whether to call cleanup before exiting (1 = yes, 0 = no).
*/
void	exit_with_error(char *msg, t_game *game, int flag)
{
	ft_putstr_fd(msg, 2);
	if (flag == 1)
		cleanup (game);
	exit (EXIT_FAILURE);
}

/*
** Validates whether a character is allowed in the map layout.
** - Acceptable characters:
**   '0' = empty space
**   '1' = wall
**   'C' = collectible
**   'E' = exit
**   'P' = player
**   'X' = enemy (optional for bonus).
**
** Parameters:
** - c: character to validate.
**
** Return:
** - 1 if valid, 0 otherwise.
*/
int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'C'
		|| c == 'E' || c == 'P' || c == 'X');
}
