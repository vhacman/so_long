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
** Checks whether the given filename ends with the ".xpm" extension.
** - Returns 1 if the f_name is at least 4 characters long and ends with ".xpm"
** - Returns 0 otherwise.
** - Prevents invalid image formats from being loaded.
**
** Parameters:
** - filename: pointer to the string containing the file name or path.
**
** Return:
** - 1 if the file ends in ".xpm", 0 if not.
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
** Loads the background image from a fixed path and stores it in the
** game structure.
** - Validates that the file extension is ".xpm".
** - Loads the image using mlx_xpm_file_to_image().
** - If loading fails, exits the program with an error.
** - The image will later be drawn repeatedly to fill the window.
**
** Parameters:
** - game: pointer to the game structure where the image is stored.
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
** Tiles the background image across the entire game window.
** - Calculates the number of columns and rows needed based on a fixed
**   tile size of 64 pixels and the window dimensions.
** - Uses nested loops to draw the image at each tile position.
** - Ensures full window coverage with no empty space.
**
** Parameters:
** - game: pointer to the game structure containing rendering context
**         and the loaded background image.
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
