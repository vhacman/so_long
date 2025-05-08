/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:46:43 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/16 14:46:43 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Updates the animation frame index for collectibles.
 * - Uses a static struct timeval variable (last_frame) to store the
 *   timestamp of the last frame update. Static ensures the variable
 *   retains its value between function calls.
 * - Calls gettimeofday() to get the current time (now).
 * - Calculates elapsed time in milliseconds between now and last_frame.
 * - If more than 200ms have passed, increments the frame index.
 * - Frame index is stored in game->collectible_frame and cycles from
 *   0 to 3 using modulo 4.
 */
void	update_collectible_frame(t_game *game)
{
	static struct timeval	last_frame = {0};
	struct timeval			now;
	long					elapsed;

	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - last_frame.tv_sec) * 1000;
	elapsed += (now.tv_usec - last_frame.tv_usec) / 1000;
	if (elapsed > 200)
	{
		game->collectible_frame = (game->collectible_frame + 1) % 4;
		last_frame = now;
	}
}

/*
 * Draws all animated collectibles based on the current frame.
 * - Calls update_collectible_frame() to ensure correct timing and
 *   frame progression.
 * - Iterates through the map grid and finds tiles marked 'C'.
 * - For each 'C', places the current animation frame using 
 *   mlx_put_image_to_window().
 * - Uses game->img_collectibles[frame] for the image to display.
 * - Each tile is rendered with a 64x64 pixel spacing to match the
 *   grid layout in the game window.
 */
void	animate_collectibles(t_game *game)
{
	int	tile_size;
	int	y;
	int	x;

	tile_size = 64;
	update_collectible_frame(game);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
			{
				mlx_put_image_to_window(game->mlx, game->window,
					game->img_collectibles[game->collectible_frame],
					x * tile_size, y * tile_size);
			}
			x++;
		}
		y++;
	}
}
