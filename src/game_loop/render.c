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
** Determines whether a sufficient number of frames have passed
** to trigger program termination after a win.
** - Uses a static variable `frame_count` to persist across calls.
** - Increments the counter every frame.
** - Returns 1 when 720 frames have passed (approx. 12 seconds at 60 FPS).
**
** Return:
** - 1
*/
static int	should_exit_after_delay(void)
{
	static int	frame_count = 0;

	frame_count++;
	return (frame_count >= 720);
}

/*
** Displays the win screen and exits the program after a delay.
** - If the win image has not yet been shown, it is rendered once at
**   the center of the window and the `shown` flag is set.
** - On subsequent calls, checks if the delay period has passed
**   using `should_exit_after_delay()`.
** - If yes, performs cleanup and terminates the program.
**
** Parameters:
** - game: pointer to the game structure with rendering state.
** - shown: pointer to static flag used to ensure image is shown only once.
**
** Return:
** - Always returns 0 to comply with MLX hook signature.
*/
static int	handle_win(t_game *game, int *shown)
{
	int	x;
	int	y;

	if (!*shown)
	{
		x = (game->window_width - game->img_win_width) / 2;
		y = (game->window_height - game->img_win_height) / 2;
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_win, x, y);
		*shown = 1;
	}
	else if (should_exit_after_delay())
	{
		cleanup(game);
		exit(0);
	}
	return (0);
}

/*
** Main rendering loop called repeatedly by MLX after the intro phase.
** - If `game->won` is true, initiates the win sequence via `handle_win()`.
** - Uses a static flag to track whether the win image was already shown.
**
** Parameters:
** - game: pointer to the game structure used throughout the loop.
**
** Return:
** - Always returns 0 to comply with MLX loop hook requirements.
*/
int	game_loop(t_game *game)
{
	static int	shown = 0;

	if (game->won == 1)
		handle_win(game, &shown);
	return (0);
}

/*
** Draws static collectible items on all tiles marked with 'C'.
** - Assumes tile size of 64 pixels.
** - Iterates through the map grid and places `img_collectible`
**   at the corresponding screen coordinates for each 'C' tile.
**
** Parameters:
** - game: pointer to the game structure containing map and image data.
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
** Redraws the full game screen by calling all necessary render functions
** in correct order to preserve visual layering.
** - Background tiles are drawn first to cover the entire window.
** - Walls, collectibles, player, exit, and blocked message are drawn
**   in sequence to overlay foreground elements.
**
** Parameters:
** - game: pointer to the game structure containing all game state and assets.
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
