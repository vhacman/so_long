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
 * Loads the introductory splash screen image.
 * - Path: "src/textures/intro.xpm".
 * - Uses mlx_xpm_file_to_image() to load the image into game->img_intro.
 * - Retrieves image dimensions and stores them in game->intro_width and
 *   game->intro_height for later centering on screen.
 * - If loading fails, exits immediately with an error.
 * - Sets game->intro_shown = 0 
 *   to indicate that the intro has not been displayed yet.
 * - This image is shown at the beginning before the game starts.
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
