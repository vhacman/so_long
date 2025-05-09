/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_lost.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:27:26 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/14 16:27:26 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Loads the intro image from an XPM file and stores it in the 
** `img_intro` field of the game structure. The image is loaded from 
** the path "src/textures/intro.xpm" using MLX.
** Also retrieves and stores the image dimensions in `intro_width` and 
** `intro_height`, used for centering during rendering.
**
** If the image fails to load, the program exits via `exit_with_error`.
** Sets `intro_shown` to 0 to indicate that the intro has not been displayed yet.
**
** Parameters:
** - game: pointer to the game structure where the image and dimensions
**         will be stored, and where error handling context resides.
*/
void	load_intro_image(t_game *game)
{
	game->img_intro = mlx_xpm_file_to_image(game->mlx,
			"src/textures/intro.xpm",
			&game->intro_width, &game->intro_height);
	if (!game->img_intro)
		exit_with_error("Error\nFailed to load intro image\n", game, 1);
	game->intro_shown = 0;
}

/*
 * Loads the image that is displayed when the player wins.
 * - Path: "src/textures/won.xpm".
 * - Uses mlx_xpm_file_to_image() to load the image and stores the result
 *   in game->img_win.
 * - Stores width and height in game->img_win_width and game->img_win_height.
 * - If the image fails to load, exits with an error message.
 * - This image is used in the game loop to indicate victory.
 */
void	load_win_image(t_game *game)
{
	game->img_win_width = 0;
	game->img_win_height = 0;
	game->img_win = mlx_xpm_file_to_image(game->mlx,
			"src/textures/won.xpm",
			&game->img_win_width, &game->img_win_height);
	if (!game->img_win)
		exit_with_error("Error\nFailed to load win image\n", game, 1);
}
