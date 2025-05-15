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
** load_player:
** - Loads two separate XPM images for the player character, one for
**   facing right and one for facing left.
** - Validates file extensions before attempting to load:
**     - "src/textures/player_right.xpm"
**     - "src/textures/player_left.xpm"
** - Loads both images using mlx_xpm_file_to_image, which reads the XPM
**   file and creates an MLX image pointer.
** - Image dimensions (width and height) are retrieved but discarded.
** - If either image fails to load (returns NULL), exits the program with
**   a corresponding error message and frees resources via exit_with_error.
** - Sets game->player_direction to 1, indicating the initial orientation
**   of the player is right-facing. This will determine which sprite is
**   used when drawing the player.
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
** draw_player:
** - Draws the correct player sprite onto the game window based on
**   the direction the player is currently facing.
** - Uses game->player_direction to select the image:
**     - If 1 → draw img_player_right
**     - If -1 → draw img_player_left
** - Converts logical player coordinates (player_x, player_y) to
**   pixel coordinates by multiplying by tile size (64), since each
**   tile occupies a 64x64 region on screen.
** - Calls mlx_put_image_to_window with:
**     - game->mlx: the MLX context
**     - game->window: the active game window
**     - the selected player image
**     - x position: player_x * 64
**     - y position: player_y * 64
** - Ensures the player is drawn at the correct position with the
**   correct sprite image depending on movement direction.
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
