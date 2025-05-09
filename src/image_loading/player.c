/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:12:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/04 22:19:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Loads the player sprite images.
 * - Verifies the presence of two .xpm files: player_right.xpm
 *    and player_left.xpm.
 * - Uses has_xpm_extension() to ensure the file format is correct.
 * - Uses mlx_xpm_file_to_image() to load each image into MLX.
 *   → Requires img_width and img_height (not used here).
 * - Stores the right-facing image in game->img_player_right.
 * - Stores the left-facing image in game->img_player_left.
 * - Sets game->player_direction to 1 (right) by default.
 * - If either image fails to load, calls exit_with_error() to terminate.
 */
void	load_player(t_game *game)
{
	int	img_width;
	int	img_height;

	if (!has_xpm_extension("src/textures/player_right.xpm"))
		exit_with_error("Player image (right) must be .xpm\n", game, 1);
	game->img_player_right = mlx_xpm_file_to_image(game->mlx,
			"src/textures/player_right.xpm", &img_width,
			&img_height);
	if (!game->img_player_right)
		exit_with_error("Failed to upload player image(right)\n", game, 1);
	if (!has_xpm_extension("src/textures/player_left.xpm"))
		exit_with_error("Player image (left) must be .xpm\n", game, 1);
	game->img_player_left = mlx_xpm_file_to_image(game->mlx,
			"src/textures/player_left.xpm", &img_width,
			&img_height);
	if (!game->img_player_left)
		exit_with_error("Failed to upload player image(left)\n", game, 1);
	game->player_direction = 1;
}

/*
 * Draws the player sprite based on its current direction.
 * - Tile size is assumed to be 64x64 pixels.
 * - Checks game->player_direction:
 *   → 1 = facing right → draw img_player_right.
 *   → -1 = facing left → draw img_player_left.
 * - Uses player_x and player_y to compute pixel coordinates.
 * - Calls mlx_put_image_to_window() to render the correct sprite
 *   at (player_x * 64, player_y * 64) on the game window.
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
