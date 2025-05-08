/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:36:38 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 15:36:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Determines if 2 full seconds have passed since the win time.
 * - Uses gettimeofday() to get current system time (now) with second
 *   and microsecond precision (struct timeval).
 * - Compares only the seconds field (tv_sec) of now and game->win_time.
 * - Returns 1 if the difference in seconds is >= 2, otherwise returns 0.
 * - This delay is used to keep the win image on screen before exiting.
 */
static int	should_exit_after_delay(t_game *game)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - game->win_time.tv_sec) >= 2);
}

/*
 * Handles the win state display and delayed program termination.
 * - If the win image has not yet been shown (shown == 0):
 *   → Calculates screen center using window dimensions and image size.
 *   → Displays the win image at the center using mlx_put_image_to_window().
 *   → Stores the current time into game->win_time using gettimeofday()
 *     to later measure how long the win image has been displayed.
 *   → Sets *shown = 1 to ensure this block is executed only once.
 * - If the image has already been shown:
 *   → Calls should_exit_after_delay() to check if 2 seconds passed.
 *   → If yes, calls cleanup() to free all resources, then exits.
 * - Ensures the win screen is visible before exiting the game.
 */
static int	handle_win(t_game *game, int *shown)
{
	int	x;
	int	y;

	if (!*shown)
	{
		x = (game->window_width - game->img_win_width) / 2;
		y = (game->window_height - game->img_win_height) / 2;
		mlx_put_image_to_window(game->mlx, game->window, game->img_win, x, y);
		gettimeofday(&game->win_time, NULL);
		*shown = 1;
	}
	else if (should_exit_after_delay(game))
	{
		cleanup(game);
		exit(0);
	}
	return (0);
}

/*
 * Game loop function registered with mlx_loop_hook.
 * - Executed every frame.
 * - Manages delayed shutdown after a win condition is triggered.
 * - Uses a static variable (shown) to ensure win image is displayed once.
 * - Continuously checks if it’s time to exit the game after showing the win.
 * - Returns 0 to comply with MLX hook function requirements.
 */
int	game_loop(t_game *game)
{
	static int	shown = 0;

	if (game->won == 1)
		handle_win(game, &shown);
	return (0);
}

/*
 *   Draws static collectible tiles on the map.
 * - Iterates through the entire game->map array.
 * - For every tile containing 'C' (collectible), calculates its screen
 *   position based on a 64-pixel tile size.
 * - Calls mlx_put_image_to_window() to draw game->img_collectible at
 *   (x * 64, y * 64).
 * - Used instead of animated collectibles in the mandatory version.
 */
void	draw_collectibles(t_game *game)
{
	int	tile_size;
	int	x;
	int	y;

	tile_size = 64;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->window,
					game->img_collectible, x * tile_size, y * tile_size);
			x++;
		}
		y++;
	}
}

/*
 * Renders all visible components of the game screen.
 * - Calls in correct order to layer tiles properly:
 *   → draw_background() first to cover the full screen.
 *   → draw_walls() overlays wall tiles on top.
 *   → draw_collectibles() places each collectible at its map position.
 *   → draw_player() places the player sprite.
 *   → draw_exit() places the exit tile image at its fixed location.
 *   → draw_blocked_exit_message() optionally shows a warning if the
 *     player steps on the exit without collecting all collectibles.
 * - This function is triggered after every state change to update display.
 */
void	render(t_game *game)
{
	draw_background(game);
	draw_walls(game);
	draw_collectibles(game);
	draw_player(game);
	draw_exit(game);
	draw_blocked_exit_message(game);
}
