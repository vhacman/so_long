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
 * Initializes the MiniLibX context and creates the game window.
 * - Calls mlx_init() to start the MLX graphical system.
 * - If initialization fails, prints an error and exits.
 * - Creates a new window using mlx_new_window() with given width,
 *   height, and title.
 * - If window creation fails, prints an error and exits.
 * - Saves width and height in game struct for later use.
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
