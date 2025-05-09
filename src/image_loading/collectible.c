/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:45:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/07 10:00:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Displays the "exit blocked" message at the center of the window.
** Only renders the image if `blocked_msg_shown` is non-zero.
** The image is shown for a limited number of frames, controlled by
** `blocked_msg_counter`, which is incremented on each call until it 
** reaches 0.5. After that, both `blocked_msg_shown` and the counter 
** are reset to disable the message display.
**
** Parameters:
** - game: a pointer to the game structure containing rendering context,
**         message flags, image pointer, and window dimensions.
*/
void	draw_blocked_exit_message(t_game *game)
{
	if (!game->blocked_msg_shown)
		return ;
	if (game->blocked_msg_counter < 0.5)
	{
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_blocked_exit,
			(game->window_width - game->blocked_exit_width) / 2,
			(game->window_height - game->blocked_exit_height) / 2);
		game->blocked_msg_counter++;
	}
	else
	{
		game->blocked_msg_shown = 0;
		game->blocked_msg_counter = 0;
	}
}

/*
** Loads the "exit blocked" banner image from the XPM file and stores it
** in the `img_blocked_exit` pointer within the game structure.
** The image is expected at path "src/textures/banner.xpm".
** Also stores the image width and height into `blocked_exit_width`
** and `blocked_exit_height` for positioning during rendering.
**
** If the image fails to load, the program is terminated using
** `exit_with_error`, releasing all allocated resources.
**
** Parameters:
** - game: a pointer to the game structure containing MLX context and
**         image-related fields.
*/
void	load_blocked_exit_image(t_game *game)
{
	game->img_blocked_exit = mlx_xpm_file_to_image(game->mlx,
			"src/textures/banner.xpm",
			&game->blocked_exit_width, &game->blocked_exit_height);
	if (!game->img_blocked_exit)
		exit_with_error("Error\nFailed to load blocked exit image\n", game, 1);
}

/*
 * Loads the main collectible image used in the mandatory part.
 * - Path: "src/textures/collectible_0.xpm".
 * - Checks that the path has the .xpm extension.
 * - Loads the image with mlx_xpm_file_to_image().
 * - Stores the pointer in game->img_collectible.
 * - Width and height are required by MLX but not stored.
 * - If the image fails to load, exits with an error.
 * - Only a static (non-animated) collectible is used here.
 */
void	load_collectible(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*path = "src/textures/collectible_0.xpm";

	if (!has_xpm_extension(path))
		exit_with_error("Error\nCollectible file must be .xpm\n", game, 1);
	game->img_collectible = mlx_xpm_file_to_image(
			game->mlx, (char *)path, &img_width, &img_height);
	if (!game->img_collectible)
		exit_with_error("Error\nFailed to load collectible image\n", game, 1);
}
