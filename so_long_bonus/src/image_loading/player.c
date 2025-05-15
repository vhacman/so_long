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
** load_player:
** - Loads the player's sprite images facing left and right.
**
** Steps:
** 1. Validates that both image files have a ".xpm" extension.
** 2. Loads the right-facing sprite from:
**      "so_long_bonus/src/textures/player_right.xpm"
**    and stores it in game->img_player_right.
** 3. Loads the left-facing sprite from:
**      "so_long_bonus/src/textures/player_left.xpm"
**    and stores it in game->img_player_left.
** 4. Initializes the player's facing direction to 1 (right).
** 5. If either image fails to load, the program exits with an error.
**
** Required:
** - game->mlx must be initialized before this function is called.
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
** draw_player:
** - Draws the player sprite at its current position on the game window.
**
** Steps:
** 1. Converts grid position (player_x, player_y) to pixel coordinates
**    by multiplying by the tile size (64 pixels).
** 2. Selects the sprite image based on game->player_direction:
**      - If 1: uses the right-facing sprite.
**      - If -1: uses the left-facing sprite.
** 3. Uses mlx_put_image_to_window to render the sprite on the screen.
**
** Assumptions:
** - The player sprite has already been loaded via load_player().
** - Direction is set based on the most recent movement input.
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
