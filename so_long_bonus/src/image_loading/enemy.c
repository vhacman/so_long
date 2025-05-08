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
 * Builds the enemy's movement path using depth-first search.
 * - Starts from (x, y) and recursively explores 4 directions.
 * - Skips tiles that are out of bounds, walls ('1'), or already visited.
 * - Stops recursion if enemy_path_len exceeds MAX_PATH to avoid overflow.
 * - Stores each step in enemy_path and marks the tile as visited.
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
 * Allocates memory for pathfinding structures.
 * - visited[][] is a 2D matrix to track explored tiles during DFS.
 * - enemy_path[] stores coordinates for the enemy's route.
 * - Exits the program if memory allocation fails at any step.
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
 * Initializes the enemy’s pathfinding and state.
 * - Sets initial position and direction.
 * - Allocates memory for visited and path arrays.
 * - Generates the path using DFS from given (x, y).
 * - If no path is found, releases memory and exits with error.
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
 * Loads XPM images for the enemy’s left and right directions.
 * - Validates file extensions to ensure .xpm format.
 * - Loads images into img_enemy_right and img_enemy_left.
 * - Exits with an error if image loading fails.
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
 * Loads enemy sprite images for left and right movement.
 * - Files: enemy_right.xpm and enemy_left.xpm.
 * - Stores result in game->img_enemy_right and game->img_enemy_left.
 * - Exits with error if either load fails.
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
