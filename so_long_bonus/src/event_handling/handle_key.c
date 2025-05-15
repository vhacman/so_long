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

#include "so_long_bonus.h"

/*
** handle_key:
** - Responds to keyboard input during active gameplay.
** - If the ESC key is pressed (KEY_ESC), triggers cleanup and exits the game.
** - If movement keys are pressed:
**     - W or UP    → move up    → move_player(game, 0, -1)
**     - S or DOWN  → move down  → move_player(game, 0, 1)
**     - A or LEFT  → move left  → move_player(game, -1, 0)
**     - D or RIGHT → move right → move_player(game, 1, 0)
** - move_player handles validation, movement logic, and rendering.
** - Always returns 0 as required by MLX key hook callback signature.
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
