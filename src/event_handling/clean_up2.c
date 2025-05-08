/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 06:12:34 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/03 11:47:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Resets all image pointers in the game struct to NULL.
 * - Prevents use-after-free errors by clearing all image references.
 * - Includes all major graphical assets: player (left/right), wall,
 *   exit, background, collectible, win, and lost screens.
 */
void	null_all_images(t_game *game)
{
	game->img_player_right = NULL;
	game->img_player_left = NULL;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_background = NULL;
	game->img_collectible = NULL;
	game->img_win = NULL;
	game->img_lost = NULL;
	game->img_blocked_exit = NULL;
}

/*
 * Frees all static image assets used in the game.
 * - Destroys each image using mlx_destroy_image() if both the MLX
 *   context and image pointer are valid.
 * - Covers all non-animated images including:
 *   intro screen, player sprites, wall, exit, blocked exit,
 *   background, collectible, win, and lost images.
 * - Avoids double free or invalid memory access by checking pointers.
 */
void	free_static_images(t_game *game)
{
	if (game->mlx && game->img_blocked_exit)
		mlx_destroy_image(game->mlx, game->img_blocked_exit);
	if (game->mlx && game->img_intro)
		mlx_destroy_image(game->mlx, game->img_intro);
	if (game->mlx && game->img_player_right)
		mlx_destroy_image(game->mlx, game->img_player_right);
	if (game->mlx && game->img_player_left)
		mlx_destroy_image(game->mlx, game->img_player_left);
	if (game->mlx && game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->mlx && game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->mlx && game->img_background)
		mlx_destroy_image(game->mlx, game->img_background);
	if (game->mlx && game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->mlx && game->img_win)
		mlx_destroy_image(game->mlx, game->img_win);
	if (game->mlx && game->img_lost)
		mlx_destroy_image(game->mlx, game->img_lost);
}
