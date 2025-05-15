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
 ** null_all_images:
 ** Sets all image pointers in the game struct to NULL.
 ** Prevents access to freed memory by clearing image pointers.
 ** Avoids destroying freed resources in later cleanup calls.
 ** Resets static and animated image pointers to a safe state.
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
 ** free_static_images:
 ** Frees all static (non-animated) image resources.
 ** Checks mlx context and image pointer before destroying.
 ** Prevents segmentation faults by validating pointers.
 ** Frees images such as backgrounds, walls, player, enemy, UI.
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
 ** free_animated_images:
 ** Frees all animated image resources (collectible frames).
 ** Iterates over animation frame array, freeing each image.
 ** Validates mlx context and image pointers before freeing.
 ** Ensures no leaks for dynamically loaded animation frames.
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
