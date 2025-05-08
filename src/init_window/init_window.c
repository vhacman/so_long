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

#include "so_long.h"

/*
 * Initializes the MiniLibX graphical context and creates the game window.
 * - Calls mlx_init() to initialize MLX. Returns a pointer to the MLX instance.
 *   → If NULL, MLX failed to initialize → print error and exit.
 * - Calls mlx_new_window() to open a window with given width, height, and title.
 *   → If NULL, window creation failed → print error and exit.
 * - Stores the window dimensions in game->window_width and game->window_height.
 * - Required before any rendering can occur (images, text, events).
 * - Must be called after calculating window size based on map dimensions.
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
