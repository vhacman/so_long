/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:01:13 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 15:01:13 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Checks if the map file has a ".ber" extension.
 * - Computes the string length.
 * - Compares the last 4 characters to ".ber".
 * - Returns 1 if match, 0 otherwise.
 */
static int	has_ber_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
}

/*
 * Loads all game assets and renders them.
 * - Loads and draws background, walls, player, enemy, and exit.
 * - Loads animated collectibles and win/loss images.
 * - Ensures that all visual elements are initialized before gameplay.
 */
static void	load_assets(t_game *game)
{
	load_background(game);
	draw_background(game);
	load_wall(game);
	draw_walls(game);
	load_player(game);
	draw_player(game);
	load_enemy(game);
	draw_enemy(game);
	load_collectible(game);
	animate_collectibles(game);
	load_exit(game);
	draw_exit(game);
	load_win_image(game);
	load_lost_image(game);
	load_blocked_exit_image(game);
}

/* 
 * Initializes the game map and window.
 * - Constructs the full map path and loads the map.
 * - Cleans map lines, validates characters and layout.
 * - Validates the path from player to exit.
 * - Calculates window dimensions based on tile size.
 * - Creates the window using init_window().
 * - Exits with error if any step fails.
 */
static void	init_game(t_game *game, char *map_name, int *win_width,
						int *win_height)
{
	char	full_path[256];
	int		tile_size;

	game->won = 0;
	tile_size = 64;
	ft_strlcpy(full_path, "src/maps/", sizeof(full_path));
	ft_strlcat(full_path, map_name, sizeof(full_path));
	load_map(game, full_path);
	clean_map(game);
	game->map_width = ft_strlen(game->map[0]);
	validate_map(game);
	if (!validate_path(game))
		exit_with_error("Error\nNo Valid Path\n", game, 1);
	*win_width = game->map_width * tile_size;
	*win_height = game->map_height * tile_size;
	init_window(game, *win_width, *win_height, "So Long");
}

/*
 * Validates command-line arguments.
 * - Requires exactly one argument: the map filename.
 * - Checks that the filename ends in ".ber".
 * - Exits with an error message if validation fails.
 */
static void	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long map1.ber\n", 2);
		exit(1);
	}
	if (!has_ber_extension(argv[1]))
	{
		ft_putstr_fd("Error\nMap file must have .ber extension\n", 2);
		exit(1);
	}
}

/*
 * Entry point of the program.
 * - Validates input arguments.
 * - Initializes the game map, assets, and window.
 * - Displays intro image for 2 seconds.
 * - Loads all game textures and sets up input and loop hooks.
 * - Starts the MLX event loop for real-time updates.
 */
int	main(int argc, char **argv)
{
	t_game	game;
	int		win_width;
	int		win_height;

	ft_bzero(&game, sizeof(t_game));
	check_args(argc, argv);
	init_game(&game, argv[1], &win_width, &win_height);
	load_intro_image(&game);
	mlx_put_image_to_window(game.mlx, game.window,
		game.img_intro,
		(game.window_width - game.intro_width) / 2,
		(game.window_height - game.intro_height) / 2);
	mlx_do_sync(game.mlx);
	sleep(2);
	load_assets(&game);
	mlx_hook(game.window, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.window, 17, 0, handle_destroy, &game);
	mlx_loop_hook(game.mlx, update_enemy, &game);
	mlx_loop(game.mlx);
	return (0);
}
