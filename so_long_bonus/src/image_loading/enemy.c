/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>         +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:30:00 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 14:30:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** build_enemy_path:
** - Performs depth-first search (DFS) to construct the enemy's movement path.
**
** Logic:
** 1. If coordinates are out of bounds, a wall, or already visited → return.
** 2. If enemy_path_len exceeds MAX_PATH → return to avoid overflow.
** 3. Mark current tile as visited and store its coordinates in enemy_path[].
** 4. Recursively explore all four directions: right, left, down, up.
**
** Purpose:
** - Builds a sequence of walkable positions for the enemy to follow.
*/
static void	build_enemy_path(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return ;
	if (game->map[y][x] == '1' || game->visited[y][x])
		return ;
	if (game->enemy_path_len >= MAX_PATH)
		return ;
	game->visited[y][x] = 1;
	game->enemy_path[game->enemy_path_len].x = x;
	game->enemy_path[game->enemy_path_len].y = y;
	game->enemy_path_len++;
	build_enemy_path(game, x + 1, y);
	build_enemy_path(game, x - 1, y);
	build_enemy_path(game, x, y + 1);
	build_enemy_path(game, x, y - 1);
}

/*
** generate_enemy_path:
** - Prepares and triggers the enemy pathfinding process.
**
** Steps:
** 1. Resets all values in game->visited[][] to 0.
** 2. Initializes enemy_path_len to 0.
** 3. Calls build_enemy_path to recursively fill game->enemy_path[].
**
** Parameters:
** - game: pointer to the game state.
** - x, y: starting position for the enemy’s DFS path generation.
*/
static void	generate_enemy_path(t_game *game, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			game->visited[i][j] = 0;
			j++;
		}
		i++;
	}
	game->enemy_path_len = 0;
	build_enemy_path(game, x, y);
}

/*
** allocate_enemy_data:
** - Allocates dynamic memory for enemy pathfinding structures.
**
** Allocates:
** 1. game->visited: 2D array of ints used to mark explored tiles during DFS.
** 2. game->enemy_path: array of t_point structs storing the enemy route.
**
** On failure:
** - Exits with an error using exit_with_error.
**
** Required before calling any path generation function.
*/
static void	allocate_enemy_data(t_game *game)
{
	int	i;

	game->visited = ft_calloc(game->map_height, sizeof(int *));
	if (!game->visited)
		exit_with_error("Error\nCalloc failed for visited\n", game, 1);
	i = 0;
	while (i < game->map_height)
	{
		game->visited[i] = ft_calloc(game->map_width, sizeof(int));
		if (!game->visited[i])
			exit_with_error("Error\nCalloc failed for visited[i]\n", game, 1);
		i++;
	}
	game->enemy_path = ft_calloc(MAX_PATH, sizeof(t_point));
	if (!game->enemy_path)
		exit_with_error("Error\nCalloc failed for enemy_path\n", game, 1);
}

/*
** init_enemy_path:
** - Entry point to initialize the enemy's state and movement logic.
**
** Steps:
** 1. Sets enemy starting position and direction.
** 2. Allocates memory for pathfinding structures via allocate_enemy_data.
** 3. Calls generate_enemy_path to compute movement path from (x, y).
** 4. If no valid path is found (enemy_path_len == 0), frees all enemy
**    resources and exits with an error.
**
** Parameters:
** - game: pointer to the main game structure.
** - x, y: starting coordinates of the enemy on the map.
*/
void	init_enemy_path(t_game *game, int x, int y)
{
	game->enemy_x = x;
	game->enemy_y = y;
	game->enemy_dir = 1;
	allocate_enemy_data(game);
	game->enemy_path_index = 0;
	game->enemy_path_len = 0;
	generate_enemy_path(game, x, y);
	if (game->enemy_path_len == 0)
	{
		free_enemy_resources(game);
		exit_with_error("Error\nEnemy path could not be generated\n", game, 1);
	}
}

/*
** load_enemy_images:
** - Loads the enemy’s sprite images for both directions (left/right).
**
** Steps:
** 1. Validates that both image paths have the ".xpm" extension.
** 2. Loads:
**     - Right-facing enemy sprite into game->img_enemy_right.
**     - Left-facing enemy sprite into game->img_enemy_left.
** 3. Uses mlx_xpm_file_to_image to load images and store their width/height.
** 4. If loading fails for either image, exits with an error.
**
** File paths:
** - "so_long_bonus/src/textures/enemy_right.xpm"
** - "so_long_bonus/src/textures/enemy_left.xpm"
*/
void	load_enemy_images(t_game *game)
{
	int			img_width;
	int			img_height;
	const char	*right = "so_long_bonus/src/textures/enemy_right.xpm";
	const char	*left = "so_long_bonus/src/textures/enemy_left.xpm";

	if (!has_xpm_extension(right))
		exit_with_error("file must have .xpm ext\n", game, 1);
	if (!has_xpm_extension(left))
		exit_with_error("file must have .xpm ext\n", game, 1);
	game->img_enemy_right = mlx_xpm_file_to_image(
			game->mlx, (char *)right, &img_width, &img_height);
	if (!game->img_enemy_right)
		exit_with_error("Error\nCould not load enemy right img\n", game, 1);
	game->img_enemy_left = mlx_xpm_file_to_image(
			game->mlx, (char *)left, &img_width, &img_height);
	if (!game->img_enemy_left)
		exit_with_error("Error\nCould not load enemy left img\n", game, 1);
}
