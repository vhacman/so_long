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
** update_collectible_frame:
** - Controls timing for collectible animation updates.
** - Uses a static struct timeval to store the last update time.
** - This variable retains its value between function calls.
** - On each call, gets the current time using gettimeofday().
** - Calculates how many milliseconds have passed since last update.
** - If more than 200ms passed, advances game->collectible_frame.
** - Frame index cycles from 0 to 3 using modulo 4.
** - Updates last_frame to the current time to restart the timer.
** - Ensures consistent animation speed independent of loop rate.
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
** animate_collectibles:
** - Renders all collectible tiles using the correct animation frame.
** - First updates frame index by calling update_collectible_frame().
** - Then scans the map for tiles marked with 'C' (collectibles).
** - For each 'C', calculates screen coordinates (x * 64, y * 64).
** - Draws the current frame image using mlx_put_image_to_window().
** - Uses game->img_collectibles[game->collectible_frame] as source.
** - Ensures all collectibles appear animated during gameplay.
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
