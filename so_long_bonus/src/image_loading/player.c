/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:12:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 15:12:13 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Loads the player character's sprite images for both directions.
 * - Verifies both files have .xpm extensions before loading.
 * - Loads player_right.xpm and player_left.xpm using MLX.
 * - Stores images in game->img_player_right and img_player_left.
 * - Sets game->player_direction to 1 (facing right) by default.
 * - Exits with an error if either image fails to load properly.
 */
void	load_player(t_game *game)
{
	int	img_width;
	int	img_height;

	if (!has_xpm_extension("so_long_bonus/src/textures/player_right.xpm"))
		exit_with_error("Player image (right) must be .xpm\n", game, 1);
	game->img_player_right = mlx_xpm_file_to_image(game->mlx,
			"so_long_bonus/src/textures/player_right.xpm",
			&img_width, &img_height);
	if (!game->img_player_right)
		exit_with_error("Failed to upload player image(right)\n", game, 1);
	if (!has_xpm_extension("so_long_bonus/src/textures/player_left.xpm"))
		exit_with_error("Player image (left) must be .xpm\n", game, 1);
	game->img_player_left = mlx_xpm_file_to_image(game->mlx,
			"so_long_bonus/src/textures/player_left.xpm",
			&img_width, &img_height);
	if (!game->img_player_left)
		exit_with_error("Failed to upload player image(left)\n", game, 1);
	game->player_direction = 1;
}

/*
 * Draws the player at their current grid position.
 * - Uses a tile size of 64 pixels for coordinate scaling.
 * - Chooses image based on game->player_direction:
 *   1 = right-facing, -1 = left-facing.
 * - Calls mlx_put_image_to_window() to render sprite.
 */
void	draw_player(t_game *game)
{
	int	tile_size;

	tile_size = 64;
	if (game->player_direction == 1)
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_player_right,
			game->player_x * tile_size, game->player_y * tile_size);
	else
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_player_left,
			game->player_x * tile_size, game->player_y * tile_size);
}
