/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 11:20:33 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/03 11:20:33 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** spawn_enemy:
** - Locates the first available empty tile ('0') on the map to place the enemy.
**
** Steps:
** 1. Iterates over the entire 2D map grid.
** 2. When a '0' tile is found, calls init_enemy_path() to:
**     - Set the enemy’s starting position.
**     - Generate its movement path.
** 3. If no empty tile is found, terminates with an error.
**
** Purpose:
** - Dynamically spawns the enemy in a valid location at runtime.
*/
void	spawn_enemy(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '0')
			{
				init_enemy_path(game, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	exit_with_error("Error\nNo white spaces for enemy spawn\n", game, 1);
}

/*
** load_enemy:
** - Initializes all enemy-related assets and state.
**
** Steps:
** 1. Loads the enemy's sprite images (left and right) via load_enemy_images().
** 2. Finds a valid tile and spawns the enemy using spawn_enemy().
**
** Assumptions:
** - This function is called once during the game's asset loading phase.
** - Requires game->map to be fully loaded and validated.
*/
void	load_enemy(t_game *game)
{
	load_enemy_images(game);
	spawn_enemy(game);
}

/*
** draw_enemy:
** - Renders the enemy sprite at its current position in the game window.
**
** Steps:
** 1. Converts grid coordinates (enemy_x, enemy_y) to pixel coordinates by
**    multiplying by the tile size (64).
** 2. Selects the correct sprite:
**     - img_enemy_right if enemy_dir == 1.
**     - img_enemy_left otherwise.
** 3. Draws the selected sprite using mlx_put_image_to_window.
**
** Purpose:
** - Visualizes the enemy in its current location and orientation.
*/
void	draw_enemy(t_game *game)
{
	int	tile_size;

	tile_size = 64;
	if (game->enemy_dir == 1)
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_enemy_right, game->enemy_x * tile_size,
			game->enemy_y * tile_size);
	else
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_enemy_left, game->enemy_x * tile_size,
			game->enemy_y * tile_size);
}

/*
** free_enemy_resources:
** - Releases memory allocated for enemy pathfinding.
**
** Steps:
** 1. Frees each row of the visited matrix, if it exists.
** 2. Frees the visited pointer array.
** 3. Frees the enemy_path array storing the enemy’s route.
** 4. Sets both pointers (visited and enemy_path) to NULL
**  to avoid dangling references.
**
** Called:
** - On game exit or when path generation fails.
*/
void	free_enemy_resources(t_game *game)
{
	int	i;

	if (game->visited)
	{
		i = 0;
		while (i < game->map_height)
		{
			if (game->visited[i])
				free(game->visited[i]);
			i++;
		}
		free(game->visited);
		game->visited = NULL;
	}
	if (game->enemy_path)
	{
		free(game->enemy_path);
		game->enemy_path = NULL;
	}
}
