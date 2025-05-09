/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:08:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 12:08:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Handles keypress events during gameplay.
** - Supports movement keys and ESC for exiting.
** - Directional keys (WASD or arrows) trigger player movement.
** - ESC key triggers cleanup and terminates the game.
** - Each movement call internally handles rendering and state updates.
**
** Parameters:
** - key: keycode of the pressed key.
** - game: pointer to the game structure containing state and context.
**
** Return:
** - Always returns 0 to conform to MLX hook function requirements.
*/
int	handle_key(int key, t_game *game)
{
	if (key == KEY_ESC)
	{
		cleanup(game);
		exit(0);
	}
	else if (key == KEY_W || key == KEY_UP)
		move_player(game, 0, -1);
	else if (key == KEY_S || key == KEY_DOWN)
		move_player(game, 0, 1);
	else if (key == KEY_A || key == KEY_LEFT)
		move_player(game, -1, 0);
	else if (key == KEY_D || key == KEY_RIGHT)
		move_player(game, 1, 0);
	return (0);
}

/*
** Handles the window close event (e.g. clicking the "X").
** - Frees all dynamically allocated game resources.
** - Terminates the program using exit(0).
**
** Parameters:
** - game: pointer to the game structure to be cleaned up.
**
** Return:
** - Always returns 0 to satisfy MLX hook signature.
*/
int	handle_destroy(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}
