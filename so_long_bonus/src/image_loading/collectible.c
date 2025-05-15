/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:45:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 14:45:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** draw_blocked_exit_message:
** - Temporarily displays a warning image when the player tries to exit
**   without collecting all required items.
**
** Steps:
** 1. If game->blocked_msg_shown is false, return immediately.
** 2. Gets the current time using gettimeofday().
** 3. Computes the time elapsed since the warning was triggered
**    by comparing it to game->blocked_msg_time.
** 4. If less than 500 milliseconds passed:
**      - Draws game->img_blocked_exit centered in the window.
** 5. If 500ms or more passed:
**      - Disables the warning by setting game->blocked_msg_shown = 0.
**
** Purpose:
** - Prevents the warning popup from staying visible indefinitely.
*/
void	draw_blocked_exit_message(t_game *game)
{
	struct timeval	now;
	long			elapsed;

	if (!game->blocked_msg_shown)
		return ;
	gettimeofday(&now, NULL);
	elapsed = (now.tv_sec - game->blocked_msg_time.tv_sec) * 1000
		+ (now.tv_usec - game->blocked_msg_time.tv_usec) / 1000;
	if (elapsed < 500)
	{
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_blocked_exit,
			(game->window_width - game->blocked_exit_width) / 2,
			(game->window_height - game->blocked_exit_height) / 2);
	}
	else
		game->blocked_msg_shown = 0;
}

/*
** load_blocked_exit_image:
** - Loads the popup image shown when the player steps on the exit
**   without having collected all collectibles.
**
** Steps:
** 1. Uses mlx_xpm_file_to_image to load the image from:
**      "src/textures/banner.xpm".
** 2. Stores the image pointer in game->img_blocked_exit.
** 3. Stores the image dimensions in game->blocked_exit_width and
**    game->blocked_exit_height.
** 4. If loading fails, exits the game with an error message.
**
** Required before calling draw_blocked_exit_message().
*/
void	load_blocked_exit_image(t_game *game)
{
	game->img_blocked_exit = mlx_xpm_file_to_image(game->mlx,
			"src/textures/banner.xpm",
			&game->blocked_exit_width, &game->blocked_exit_height);
	if (!game->img_blocked_exit)
		exit_with_error("Error\nFailed blocked exit image\n", game, 1);
}

/*
** load_collectible_frame:
** - Loads a single frame of the collectible animation.
**
** Parameters:
** - index: target index in game->img_collectibles[].
** - path: file path to the XPM image.
**
** Steps:
** 1. Verifies that the file path ends with ".xpm".
** 2. Loads the image using mlx_xpm_file_to_image and stores it
**    in game->img_collectibles[index].
** 3. If loading fails, exits with an error.
**
** Used internally by load_collectible().
*/
static void	load_collectible_frame(t_game *game, int index, const char *path)
{
	int	img_width;
	int	img_height;

	if (!has_xpm_extension(path))
		exit_with_error("Error\nCollectible file must be .xpm\n", game, 1);
	game->img_collectibles[index] = mlx_xpm_file_to_image(
			game->mlx, (char *)path, &img_width, &img_height);
	if (!game->img_collectibles[index])
		exit_with_error("Error\nFailed to load collectible image\n", game, 1);
}

/*
** load_collectible:
** - Loads all 4 frames of the collectible's animation.
**
** Steps:
** 1. Calls load_collectible_frame() four times with frame paths:
**    - collectible_0.xpm → collectible_3.xpm.
** 2. Initializes game->collectible_frame to 0, the starting frame.
**
** Purpose:
** - Prepares animated collectible assets before the game starts.
*/
void	load_collectible(t_game *game)
{
	load_collectible_frame(game, 0,
		"so_long_bonus/src/textures/collectible_0.xpm");
	load_collectible_frame(game, 1,
		"so_long_bonus/src/textures/collectible_1.xpm");
	load_collectible_frame(game, 2,
		"so_long_bonus/src/textures/collectible_2.xpm");
	load_collectible_frame(game, 3,
		"so_long_bonus/src/textures/collectible_3.xpm");
	game->collectible_frame = 0;
}
