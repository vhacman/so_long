/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:47:52 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/03 11:47:52 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Sets all image pointers in the game struct to NULL.
 * - Prevents access to freed memory by clearing all image pointers.
 * - Ensures the program does not attempt to destroy already-freed
 *   resources during future cleanups.
 * - Resets both static and animated image pointers to a safe state.
 */
void	null_all_images(t_game *game)
{
	int	i;

	game->img_player_right = NULL;
	game->img_player_left = NULL;
	game->img_enemy_left = NULL;
	game->img_enemy_right = NULL;
	game->img_wall = NULL;
	game->img_exit = NULL;
	game->img_background = NULL;
	game->img_win = NULL;
	game->img_lost = NULL;
	i = 0;
	while (i < 4)
	{
		game->img_collectibles[i] = NULL;
		i++;
	}
}

/*
 * Frees all static image resources used in the game.
 * - Releases memory allocated by mlx_new_image to prevent memory leaks.
 * - Checks that both the MLX context and image pointer are valid before
 *   calling mlx_destroy_image to avoid segmentation faults.
 * - Static images include environment and UI assets that don't animate.
 */
void	free_static_images(t_game *game)
{
	if (game->mlx && game->img_intro)
		mlx_destroy_image(game->mlx, game->img_intro);
	if (game->mlx && game->img_player_right)
		mlx_destroy_image(game->mlx, game->img_player_right);
	if (game->mlx && game->img_player_left)
		mlx_destroy_image(game->mlx, game->img_player_left);
	if (game->mlx && game->img_enemy_left)
		mlx_destroy_image(game->mlx, game->img_enemy_left);
	if (game->mlx && game->img_enemy_right)
		mlx_destroy_image(game->mlx, game->img_enemy_right);
	if (game->mlx && game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->mlx && game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->mlx && game->img_background)
		mlx_destroy_image(game->mlx, game->img_background);
	if (game->mlx && game->img_win)
		mlx_destroy_image(game->mlx, game->img_win);
	if (game->mlx && game->img_lost)
		mlx_destroy_image(game->mlx, game->img_lost);
}

/*
 * Frees all animated image resources related to collectibles.
 * - Avoids memory leaks by releasing dynamically created image frames.
 * - Iterates through the array to handle all animation frames.
 * - Validates both MLX context and image pointer before destroying.
 */
void	free_animated_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->mlx && game->img_collectibles[i])
			mlx_destroy_image(game->mlx, game->img_collectibles[i]);
		i++;
	}
}
