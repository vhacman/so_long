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
** - Returns 1 when 100000 frames have passed
**
** Return:
** - 1
*/
static int	should_exit_after_delay(void)
{
	static int	frame_count = 0;

	frame_count++;
	return (frame_count >= 100000);
}

/*
** handle_win:
** - Displays the win screen and exits the game after a fixed delay.
** - If the win image hasn't been displayed yet (*shown == 0):
**     - Calculates center position of the window.
**     - Draws the image once using mlx_put_image_to_window.
**     - Sets *shown to 1 to prevent multiple renderings.
** - If the image was already shown:
**     - Calls should_exit_after_delay to wait 720 frames.
**     - When the wait is complete, cleans up and exits the program.
** - Always returns 0 to satisfy MLX loop hook requirements.
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
** draw_collectibles:
** - Iterates through the 2D map array.
** - For each tile containing 'C' (collectible), draws the collectible
**   image at the appropriate screen position (x * 64, y * 64).
** - Assumes each tile corresponds to a 64x64 pixel block.
** - Requires game->img_collectible to be preloaded.
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
** render:
** - Redraws the full game window from scratch in correct visual order.
** - Layering:
**     1. Background (covers entire window).
**     2. Walls (on top of background).
**     3. Collectibles (on floor tiles).
**     4. Player sprite.
**     5. Exit tile.
**     6. "Exit blocked" message (if active).
** - Ensures visual coherence by respecting layer priority.
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
