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
 * Displays a temporary message when the player steps on the exit
 * without collecting all collectibles.
 * - Uses gettimeofday() to get the current time (now) with
 *   second and microsecond precision.
 * - Computes the elapsed time in milliseconds since the moment
 *   the player stepped on the exit tile and the warning was triggered.
 * - If less than 500ms have passed, it draws the image
 *   game->img_blocked_exit centered on the window.
 * - If more than 500ms passed, hides the message by setting
 *   game->blocked_msg_shown = 0.
 * - Prevents the message from staying on screen indefinitely.
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
 * Loads the image used for the "blocked exit" popup.
 * - Loads the XPM file: "src/textures/banner.xpm".
 * - Stores image pointer in game->img_blocked_exit.
 * - Stores width and height of the image in
 *   game->blocked_exit_width and game->blocked_exit_height.
 * - Exits with an error if the image fails to load.
 * - This image is used in draw_blocked_exit_message().
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
 * Loads a single collectible frame image from file.
 * - Validates file extension is .xpm using has_xpm_extension().
 * - Loads the image using mlx_xpm_file_to_image().
 * - Stores the image in game->img_collectibles at the given index.
 * - Exits the program with an error if the extension is wrong or
 *   if loading fails (e.g., file missing or corrupted).
 * - img_width and img_height are required by MLX but unused.
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
 * Loads all four animation frames for the collectible item.
 * - Calls load_collectible_frame() with fixed paths for each frame.
 * - Initializes game->collectible_frame to 0 (starting frame).
 * - Ensures all necessary frames are available before animation starts.
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
