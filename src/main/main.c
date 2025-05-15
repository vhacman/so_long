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

#include "so_long.h"

/*
 * Checks if the given filename ends with ".ber".
 * - Calculates the length of the filename using ft_strlen().
 * - If length is less than 4, returns 0 (invalid).
 * - Compares the last 4 characters of the string to ".ber" using
 *   ft_strncmp().
 * - Returns 1 if match found, else 0.
 * - Used to verify that the map file has the correct extension.
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
 * Loads all static assets and draws them once.
 * - Calls load and draw functions for background, wall, player,
 *   collectible, exit, win image, and blocked-exit popup.
 * - Does not include animated elements or enemies.
 * - Ensures all required graphics are ready before game starts.
 * - This happens after intro screen and before the main loop.
 */
void	load_assets(t_game *game)
{
	load_background(game);
	draw_background(game);
	load_wall(game);
	draw_walls(game);
	load_player(game);
	draw_player(game);
	load_collectible(game);
	draw_collectibles(game);
	load_exit(game);
	draw_exit(game);
	load_win_image(game);
	load_blocked_exit_image(game);
}

/*
** init_game:
** - Initializes the game using the provided map filename.
** - Constructs full path by prepending "src/maps/" to map name.
** - Loads map lines from file using load_map.
** - Removes newline or carriage return chars using clean_map.
** - Sets map_width based on the first line's length.
** - Validates map symbols and wall boundaries.
** - Verifies that all collectibles and exit are reachable.
**   using validate_path.
** - Exits with error if path is invalid.
** - Calculates window size using map dimensions × tile size (64).
** - Opens the graphical window using init_window.
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
 * Validates command-line arguments passed to main().
 * - argc must be 2 → the program and 1 map file name.
 * - argv[1] must end in ".ber" → checked by has_ber_extension().
 * - If checks fail, prints an error and exits.
 * - Ensures the game starts only with valid input.
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
** - Zeroes out the game structure using ft_bzero.
** - Validates arguments using check_args.
** - Initializes game state and loads the map with init_game.
** - Loads the intro screen image.
** - Sets animation flags for the intro sequence.
** - Registers intro_loop as the loop hook in the MLX event system.
** - Sets up event handlers:
**   
** mlx_loop_hook(game.mlx, intro_loop, &game):
** - Registers a function (intro_loop) to be called continuously
**   on each iteration of the MLX loop.
** - This function is used for frame-by-frame logic, such as intro animation.
**
** mlx_hook(game.window, 2, 1L << 0, handle_key, &game):
** - Sets up an event hook for keypress events (event code 2).
** - 1L << 0 is the bitmask corresponding to KeyPress.
** - When a key is pressed, MLX calls handle_key with the game context.
**
** mlx_hook(game.window, 17, 0, handle_destroy, &game):
** - Sets up an event hook for window close (event code 17).
** - Triggered when the user clicks the close button of the window.
** - MLX calls handle_destroy to perform cleanup before exiting.
**
** mlx_loop(game.mlx):
** - Enters the MLX event loop, which runs indefinitely.
** - Continuously listens for registered events and updates the window.
** - This call blocks and controls the lifetime of the graphical program.
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
	game.intro_done = 0;
	game.intro_frame = 0;
	mlx_loop_hook(game.mlx, intro_loop, &game);
	mlx_hook(game.window, 2, 1L << 0, handle_key, &game);
	mlx_hook(game.window, 17, 0, handle_destroy, &game);
	mlx_loop(game.mlx);
	return (0);
}
