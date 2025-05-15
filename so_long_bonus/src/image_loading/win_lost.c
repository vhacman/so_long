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
#include "so_long_bonus.h"

/*
** load_intro_image:
** - Loads the intro screen image from "so_long_bonus/src/textures/intro.xpm".
** - Stores the image pointer in game->img_intro.
** - Also stores the image’s width and height in game->intro_width and
**   game->intro_height for later centering during display.
** - Sets game->intro_shown to 0 to indicate the intro hasn't been rendered yet.
** - If the image fails to load (returns NULL), exits the program with an error.
*/
void	load_intro_image(t_game *game)
{
	game->img_intro = mlx_xpm_file_to_image(game->mlx,
			"so_long_bonus/src/textures/intro.xpm",
			&game->intro_width, &game->intro_height);
	if (!game->img_intro)
		exit_with_error("Error\nFailed to load intro image\n", game, 1);
	game->intro_shown = 0;
}

/*
** load_lost_image:
** - Loads the "game over" image shown when the player loses.
** - File path: "so_long_bonus/src/textures/lost.xpm".
** - Loads the image into game->img_lost and stores the dimensions in
**   game->img_lost_width and game->img_lost_height.
** - No error handling shown here;
** image must be used carefully or checked elsewhere.
*/
void	load_lost_image(t_game *game)
{
	game->img_lost = mlx_xpm_file_to_image(game->mlx,
			"so_long_bonus/src/textures/lost.xpm", &game->img_lost_width,
			&game->img_lost_height);
}

/*
** load_win_image:
** - Loads the victory screen image from "so_long_bonus/src/textures/won.xpm".
** - Stores the resulting MLX image in game->img_win.
** - Retrieves the image’s width and height into game->img_win_width and
**   game->img_win_height, used to position it on screen.
** - If loading fails, the program exits immediately with an error message.
*/
void	load_win_image(t_game *game)
{
	game->img_win_width = 0;
	game->img_win_height = 0;
	game->img_win = mlx_xpm_file_to_image(game->mlx,
			"so_long_bonus/src/textures/won.xpm",
			&game->img_win_width, &game->img_win_height);
	if (!game->img_win)
		exit_with_error("Error\nFailed to load win image\n", game, 1);
}
