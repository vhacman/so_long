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
** has_ber_extension:
** - Validates that the input filename ends with ".ber".
** - Computes string length and compares last 4 characters.
** - Returns 1 if extension is correct, 0 otherwise.
** - Used to ensure only valid map files are accepted.
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
** load_assets:
** - Loads and renders all visual elements required by the game.
** - Calls loading and drawing functions in proper order:
**     - Background, wall, player, enemy, exit, collectibles, win/loss banners.
** - Loads animated collectibles and static assets.
** - Ensures all resources are ready before gameplay begins.
** - Must be called after the intro screen and before the main loop.
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
** init_game:
** - Prepares game state and window based on a given map name.
** - Constructs the full path to the map by prepending "src/maps/".
** - Loads and cleans the map from file.
** - Validates content, structure, and path accessibility.
** - Computes window dimensions based on map size (tile_size = 64).
** - Initializes the window with those dimensions and a title.
** - Exits the program on failure at any step.
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
** check_args:
** - Validates command-line input before launching the game.
** - Ensures exactly one argument is passed: the map filename.
** - Verifies that the filename ends with ".ber".
** - Prints an error and exits if checks fail.
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
** main:
** - Entry point of the program.
**
** Steps:
** 1. Clears the t_game structure with ft_bzero to avoid garbage values.
** 2. Validates CLI arguments using check_args.
** 3. Loads and validates map, sets up game state and window via init_game.
** 4. Loads and displays the intro image, centered in the window.
** 5. Waits 2 seconds (sleep) before starting the game.
** 6. Calls load_assets to load all textures and draw initial game state.
** 7. Sets up event hooks:
**     - Key input → handle_key
**     - Window close → handle_destroy
**     - Per-frame update → update_enemy
** 8. Starts the MLX loop (mlx_loop), which runs the game continuously.
**
** Returns:
** - Always returns 0 on normal termination.
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
