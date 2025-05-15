/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:31:53 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/10 11:31:53 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** init_window:
** - Initializes the graphical environment using MiniLibX.
**
** Steps:
** 1. Calls mlx_init() to set up the MLX connection. 
**     - If it fails (returns NULL), prints an error and exits immediately.
**
** 2. Creates a new game window using mlx_new_window(), passing:
**     - the MLX context (game->mlx),
**     - the desired window width and height,
**     - and the title string to be shown in the window title bar.
**     - If this call fails (returns NULL), prints an error and exits.
**
** 3. Stores the window's width and height in game->window_width and
**    game->window_height for later reference (e.g., centering images).
**
** Parameters:
** - game: pointer to the game structure which will hold the MLX context
**         and window handle.
** - width: desired width of the window in pixels.
** - height: desired height of the window in pixels.
** - title: string shown in the window's title bar.
*/
void	init_window(t_game *game, int width, int height, char *title)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_putstr_fd("Error\nMLX initialization failed\n", 2);
		exit (EXIT_FAILURE);
	}
	game->window = mlx_new_window(game->mlx, width, height, title);
	if (!game->window)
	{
		ft_putstr_fd("Error\nWindow creation failed\n", 2);
		exit (EXIT_FAILURE);
	}
	game->window_width = width;
	game->window_height = height;
}
