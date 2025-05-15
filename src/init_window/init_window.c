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
** Loop hook function executed repeatedly during the intro phase.
** Displays the intro image on the first frame by centering it in the
** window. The image remains on screen while `intro_frame` is incremented
** until it reaches 10000 frames, simulating a delay.
**
** Once the frame counter reaches the threshold, the intro ends by:
** - Setting `intro_done` to 1 to prevent repeated execution.
** - Loading the main game assets via `load_assets`.
** - Replacing the current loop hook with `game_loop` for gameplay.
**
** Parameters:
** - game: pointer to the game structure containing intro flags,
**         frame count, image, and rendering context.
**
** Return:
** - Always returns 0, as required by MLX hook conventions.
*/
int	intro_loop(t_game *game)
{
	if (!game->intro_done)
	{
		if (game->intro_frame == 0)
		{
			mlx_put_image_to_window(game->mlx, game->window,
				game->img_intro,
				(game->window_width - game->intro_width) / 2,
				(game->window_height - game->intro_height) / 2);
		}
		game->intro_frame++;
		if (game->intro_frame >= 10000)
		{
			game->intro_done = 1;
			load_assets(game);
			mlx_loop_hook(game->mlx, game_loop, game);
		}
	}
	return (0);
}

/*
** init_window:
** - Initializes the MLX graphical system using mlx_init().
** - If initialization fails, prints error and exits the program.
** - Creates a new window with given width, height, and title.
** - If window creation fails, prints error and exits the program.
** - Stores width and height in game->window_width and game->window_height.
** - Stores the returned MLX context and window handle in game->mlx and
**   game->window for later use.
**  
**   Parameters:
** - game: pointer to the game structure to store MLX and window handles.
** - width: desired width of the window in pixels.
** - height: desired height of the window in pixels.
** - title: string to be used as the window title.
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
