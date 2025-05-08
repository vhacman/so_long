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
 * Finds the first empty tile ('0') on the map and spawns the enemy there.
 * - Iterates through the 2D map grid row by row.
 * - When a free tile is found, calls init_enemy_path() to initialize
 *   enemy position and movement path.
 * - If no free tile is available, exits the program with an error.
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
 * Initializes all enemy-related state and assets.
 * - Loads enemy sprite images using load_enemy_images().
 * - Places the enemy on the map by calling spawn_enemy().
 * - Sets up its pathfinding structure for future movement.
 */
void	load_enemy(t_game *game)
{
	load_enemy_images(game);
	spawn_enemy(game);
}

/*
 * Draws the enemy sprite at its current map position.
 * - Uses a fixed tile size of 64 pixels for coordinate scaling.
 * - Displays img_enemy_right if game->enemy_dir is 1 (moving right).
 * - Otherwise displays img_enemy_left for leftward movement.
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
 * Frees memory used for enemy movement and pathfinding.
 * - Frees each row in the visited matrix if it exists.
 * - Frees the enemy_path array used for storing path steps.
 * - Sets visited and enemy_path pointers to NULL after freeing
 *   to avoid dangling references.
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
