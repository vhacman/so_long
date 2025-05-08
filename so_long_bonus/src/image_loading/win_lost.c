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
 * Loads the intro screen image displayed at game start.
 * - File: "src/textures/intro.xpm".
 * - Loads image into game->img_intro and stores its dimensions.
 * - Sets game->intro_shown to 0 to mark that it hasn't been displayed yet.
 * - Exits with an error if loading fails.
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
 * Loads the image displayed when the player wins the game.
 * - File: "src/textures/won.xpm".
 * - Loads image into game->img_win and stores its dimensions.
 * - Initializes dimensions to 0 before loading.
 * - Exits with an error if the image fails to load.
 */
void	load_lost_image(t_game *game)
{
	game->img_lost = mlx_xpm_file_to_image(game->mlx,
			"so_long_bonus/src/textures/lost.xpm", &game->img_lost_width,
			&game->img_lost_height);
}

/*
 * Loads the image to be shown when the player wins the game.
 * - File path: src/textures/won.xpm.
 * - Stores the image in game->img_win.
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
