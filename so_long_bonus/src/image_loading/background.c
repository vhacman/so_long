/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:22:04 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/08 14:42:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** has_xpm_extension:
** - Checks whether the provided filename ends with ".xpm".
**
** Steps:
** 1. Computes the length of the input string.
** 2. If the string is shorter than 4 characters, returns 0.
** 3. Otherwise, compares the last 4 characters to ".xpm".
**
** Returns:
** - 1 if the file has a valid .xpm extension.
** - 0 if not.
**
** Purpose:
** - Ensures that only valid texture files are loaded by the MLX API.
*/
int	has_xpm_extension(const char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".xpm", 4) == 0);
}

/*
** load_background:
** - Loads the background texture used to fill the game window.
**
** Steps:
** 1. Defines the path to the background file:
**      "so_long_bonus/src/textures/background.xpm".
** 2. Verifies the file extension using has_xpm_extension().
** 3. Loads the image using mlx_xpm_file_to_image and stores it
**    in game->img_background.
** 4. If loading fails, the function exits the program with an error.
**
** Notes:
** - MLX requires img_width and img_height to be passed,
**   but they are unused here.
** - The image is meant to be tiled over the window via draw_background().
*/
void	load_background(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*background_path;

	background_path = "so_long_bonus/src/textures/background.xpm";
	if (!has_xpm_extension(background_path))
		exit_with_error("Background file must have .xpm ext\n", game, 1);
	game->img_background = mlx_xpm_file_to_image(game->mlx,
			(char *)background_path, &img_width, &img_height);
	if (!game->img_background)
		exit_with_error("Error\nFailed to upload background\n", game, 1);
}

/*
** draw_background:
** - Fills the entire game window by tiling the background image.
**
** Steps:
** 1. Defines a tile size of 64 pixels (assumed constant).
** 2. Calculates how many tiles are needed horizontally and vertically.
** 3. Uses nested loops to draw the background tile at each grid position.
**    - Position = (row_index * tile_size, col_index * tile_size).
** 4. Uses mlx_put_image_to_window for each tile placement.
**
** Purpose:
** - Ensures complete visual coverage of the window with
**   repeated background tiles.
** - This function must be called before drawing walls,
**    player, collectibles, etc.
*/
void	draw_background(t_game *game)
{
	int	row_index;
	int	col_index;
	int	max_cols;
	int	max_rows;
	int	tile_size;

	tile_size = 64;
	max_cols = game->window_width / tile_size;
	max_rows = game->window_height / tile_size;
	col_index = 0;
	while (col_index < max_rows)
	{
		row_index = 0;
		while (row_index < max_cols)
		{
			mlx_put_image_to_window(game->mlx, game->window,
				game->img_background, row_index * tile_size,
				col_index * tile_size);
			row_index++;
		}
		col_index++;
	}
}
