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
** load_intro_image:
** - Loads the intro screen image from "src/textures/intro.xpm" using
**   mlx_xpm_file_to_image.
** - Stores the image pointer in game->img_intro.
** - Stores the image dimensions in game->intro_width and game->intro_height.
** - These values are used later to center the intro image on screen.
** - If loading fails, exits the program with an error message.
** - Initializes game->intro_shown to 0 to track if the intro has been displayed.
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
** load_win_image:
** - Loads the win screen image from "src/textures/won.xpm" using
**   mlx_xpm_file_to_image.
** - Stores the resulting image pointer in game->img_win.
** - Saves image dimensions in game->img_win_width and game->img_win_height.
** - These values are required for rendering the win screen correctly.
** - If loading fails, exits the program with an error message.
** - The image is used to indicate that the player has won the game.
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
