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
 * Handles keyboard input from the user during gameplay.
 * - KEY_ESC: exits the game by calling cleanup() and exit().
 * - KEY_W / KEY_UP: moves the player up.
 * - KEY_S / KEY_DOWN: moves the player down.
 * - KEY_A / KEY_LEFT: moves the player left.
 * - KEY_D / KEY_RIGHT: moves the player right.
 * - After movement, the game state is updated and render() is called
 *   externally if needed.
 * - Returns 0 to comply with MLX hook requirements.
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
 * Handles the window close event (clicking the red X).
 * - Frees all allocated game resources using cleanup().
 * - Exits the program cleanly with exit(0).
 * - Returns 0 to satisfy the MLX event hook system.
 */
int	handle_destroy(t_game *game)
{
	cleanup(game);
	exit(0);
	return (0);
}
