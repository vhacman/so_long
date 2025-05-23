/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 15:00:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Loads the exit tile image into the game structure from a file path
** defined by the EXIT_TEXTURE_PATH macro.
** - Checks the file extension using has_xpm_extension().
** - Uses mlx_xpm_file_to_image() to load the image into memory.
** - Stores the resulting image pointer in `img_exit`.
** - If the image fails to load, exits the program with an error message.
** - Width and height are read into temporary variables but not used.
**
** Parameters:
** - game: pointer to the game structure where the exit image will be stored.
*/
void	load_exit(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*exit_path;

	exit_path = EXIT_TEXTURE_PATH;
	if (!has_xpm_extension(exit_path))
		exit_with_error("file must have .xpm ext\n", game, 1);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, (char *)exit_path,
			&img_width, &img_height);
	if (!game->img_exit)
		exit_with_error("Error\nFailed to upload exit\n", game, 1);
}

/*
** draw_exit:
** - Scans the entire game map for the first tile containing 'E'
**   (the exit position).
** - Once the 'E' is found, calculates its screen position by
**   multiplying grid coordinates (x, y) by tile size (64).
** - Draws the exit image at the computed pixel coordinates using
**   mlx_put_image_to_window.
** - Immediately returns after drawing, assuming only one exit exists.
** - Requires game->map, game->img_exit, game->mlx, and game->window
**   to be properly initialized.
*/
void	draw_exit(t_game *game)
{
	int	tile_size;
	int	x;
	int	y;

	tile_size = 64;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'E')
			{
				mlx_put_image_to_window(game->mlx, game->window,
					game->img_exit, x * tile_size, y * tile_size);
				return ;
			}
			x++;
		}
		y++;
	}
}
