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
** Sets all image pointers in the game structure to NULL.
** - Prevents accidental reuse of freed images.
** - Must be called after freeing images with mlx_destroy_image().
** - Covers all static image resources: player, wall, exit,
**   background, collectibles, and end screens.
**
** Parameters:
** - game: pointer to the game structure with image fields.
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
** Frees all static images allocated with MLX during the game.
** - Each image is destroyed only if both the MLX context and image
**   pointer are valid.
** - Avoids invalid memory access by checking each image.
** - Frees intro screen, blocked message, all player sprites,
**   wall, background, collectible, exit, win, and lost images.
**
** Parameters:
** - game: pointer to the game structure containing MLX and image handles.
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
