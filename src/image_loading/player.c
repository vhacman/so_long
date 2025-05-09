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
** Loads the player's sprite images for both directions.
** - Validates that the image files have a ".xpm" extension.
** - Loads "player_right.xpm" into `img_player_right`.
** - Loads "player_left.xpm" into `img_player_left`.
** - Uses `mlx_xpm_file_to_image()` to load each image via the MLX API.
** - Sets the initial player direction to 1 (facing right).
** - If any image fails to load, terminates the program with an error.
**
** Parameters:
** - game: pointer to the game structure where image handles and state are stored.
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
** Renders the player's sprite at the correct position and orientation.
** - Uses `player_direction` to select the correct sprite image:
**   → 1 for right-facing, -1 for left-facing.
** - Computes the drawing position by scaling `player_x` and `player_y`
**   by the tile size (64 pixels).
** - Calls `mlx_put_image_to_window()` to draw the sprite in the window.
**
** Parameters:
** - game: pointer to the game structure containing player position,
**         direction, image handles, and rendering context.
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
