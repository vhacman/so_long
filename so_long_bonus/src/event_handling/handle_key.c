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
 * Handles keyboard input events triggered by the player.
 * - Pressing ESC exits the game safely by freeing all resources.
 * - Arrow keys or WASD keys move the player in the corresponding
 *   direction within the map grid.
 * - After movement, render() is called to update the game window.
 * - Ensures all input is mapped explicitly to avoid undefined behavior.
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
 * Handles the event when the window is closed by the user.
 * - Ensures the game exits cleanly by freeing all allocated memory.
 * - Avoids leaks and orphaned processes by calling cleanup().
 * - Terminates the program after resource deallocation.
 */
int	handle_destroy(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}
