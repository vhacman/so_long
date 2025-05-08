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
 * Checks if the given filename has a ".xpm" extension.
 * - Returns 1 if the filename ends with ".xpm".
 * - Returns 0 if the extension is missing or too short.
 * - Used to validate texture file format before loading.
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
 * Loads the background image into game->img_background.
 * - Uses a fixed path: "src/textures/background.xpm".
 * - Validates the file extension using has_xpm_extension().
 * - Loads the image using mlx_xpm_file_to_image().
 * - Exits with an error message if the file is missing or invalid.
 * - img_width and img_height are required by MLX but not used.
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
 * Draws the background image tiled across the full game window.
 * - Uses a fixed tile size of 64x64 pixels.
 * - Computes how many tiles fit horizontally and vertically.
 * - Iterates through each row and column, drawing the image
 *   at the appropriate pixel coordinates using MLX.
 * - Ensures full coverage of the window with repeated background tiles.
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
