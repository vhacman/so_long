/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:22:04 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 14:42:10 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Checks if a filename ends with ".xpm".
 * - Used to validate that texture files have the correct format.
 * - Computes the string length, then compares the last 4 characters.
 * - Returns 1 if the extension is correct, 0 otherwise.
 * - Prevents loading of unsupported or invalid image formats.
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
 * Loads the background image and stores it in game->img_background.
 * - Uses a hardcoded file path: "src/textures/background.xpm".
 * - Verifies the file extension is ".xpm" before attempting to load.
 * - Calls mlx_xpm_file_to_image() to load the image into memory.
 *   → This function requires width and height pointers, even if values
 *     are unused.
 * - Exits the program with an error message if the image fails to load.
 * - The background will be used to tile the entire game window.
 */
void	load_background(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*background_path;

	background_path = "src/textures/background.xpm";
	if (!has_xpm_extension(background_path))
		exit_with_error("Background file must have .xpm ext\n", game, 1);
	game->img_background = mlx_xpm_file_to_image(game->mlx,
			(char *)background_path, &img_width, &img_height);
	if (!game->img_background)
		exit_with_error("Error\nFailed to upload background\n", game, 1);
}

/*
 * Draws the background image across the entire game window.
 * - Each image tile is 64x64 pixels (tile_size = 64).
 * - Calculates how many columns and rows are needed based on the
 *   window size stored in game->window_width/height.
 * - Uses two nested loops to draw the background image repeatedly
 *   to cover the full window surface.
 * - mlx_put_image_to_window() places one image per tile location
 *   using coordinates (col * tile_size, row * tile_size).
 * - Ensures no unpainted areas by filling the screen completely.
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
