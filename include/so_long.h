/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:31:11 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/08 11:31:11 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ===================== Constants ===================== */
/*
 * Keyboard key codes for movement and ESC key.
 * Used in input handling to control player or close the window.
 */
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MAX_PATH 1024
# define EXIT_TEXTURE_PATH "src/textures/exit.xpm"

/* ===================== Libraries ===================== */
/*
 * External libraries and headers used:
 * - mlx: graphical window management
 * - libft: custom utility library
 * - get_next_line: for reading map files line-by-line
 * - standard C libraries: file handling, memory, etc.
 */
# include <mlx.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include "get_next_line.h"
# include <sys/time.h>

/* ===================== Structures ===================== */

/*
 * Represents a coordinate or 2D point on the map.
 */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/*
 * Main game structure that holds all game state, assets, and runtime data.
 * This includes window dimensions, map data, graphical assets, counters,
 * animation state, and flags for win/loss/game messages.
 */
typedef struct s_game
{
	/* Graphics context */
	void			*mlx;
	void			*window;
	int				window_width;
	int				window_height;

	/* Map */
	char			**map;
	int				map_width;
	int				map_height;

	/* Player */
	int				player_x;
	int				player_y;
	int				collectibles;
	int				moves;
	void			*img_player_right;
	void			*img_player_left;
	int				player_direction;

	/* Static environment assets */
	void			*img_background;
	void			*img_wall;
	void			*img_exit;
	void			*img_collectible;

	/* Game outcome state */
	int				won;
	int				lost;
	struct timeval	win_time;
	void			*img_win;
	int				img_win_width;
	int				img_win_height;
	void			*img_lost;

	/* Intro screen state */
	void			*img_intro;
	int				intro_shown;
	int				intro_width;
	int				intro_height;

	/* "Blocked exit" banner when player misses collectibles */
	void			*img_blocked_exit;
	int				blocked_exit_width;
	int				blocked_exit_height;
	int				blocked_msg_shown;
	struct timeval	blocked_msg_time;

}	t_game;

/* ===================== Entry Point ===================== */
/* Main program entry function defined in main.c */
int		main(int argc, char **argv);

/* ===================== Initialization ===================== */
/*
 * Functions related to setting up the game:
 * - creating the window
 * - loading the map
 * - validating input
 * - error handling
 */
void	init_window(t_game *game, int width, int height, char *title);
void	init_enemy_path(t_game *game, int x, int y);
void	load_map(t_game *game, char *filename);
void	clean_map(t_game *game);
void	validate_map(t_game *game);
int		validate_path(t_game *game);
void	exit_with_error(char *msg, t_game *game, int flag);

/* ===================== Map Validation ===================== */
/*
 * Checks and validates the structure and content of the map:
 * - valid characters
 * - wall boundaries
 * - rectangular shape
 * - reachable path to exit and collectibles
 */
int		is_valid_char(char c);
void	check_characters(t_game *game, int *p_count,
			int *e_count, int *c_count);
void	check_rectangular_and_walls(t_game *game);
int		check_remaining_elements(char **map_copy, int map_height);
void	free_map_copy(char **map_copy, int map_height);

/* ===================== Input Handling ===================== */
/*
 * Handles player keyboard inputs and window events.
 * Includes key press hooks and player movement logic.
 */
int		handle_key(int key, t_game *game);
int		_key(int key, t_game *game); // legacy or alternate input
int		handle_destroy(t_game *game);
void	move_player(t_game *game, int dx, int dy);

/* ===================== Asset Loading ===================== */
/*
 * Loads XPM texture files into MLX image pointers.
 * Includes static assets (background, wall, exit) and
 * win/loss/intro/collectible visuals.
 */
void	load_background(t_game *game);
void	load_wall(t_game *game);
void	load_player(t_game *game);
void	load_enemy(t_game *game);
void	load_enemy_images(t_game *game);
void	load_collectible(t_game *game);
void	load_exit(t_game *game);
void	load_win_image(t_game *game);
void	load_lost_image(t_game *game);
void	load_intro_image(t_game *game);
void	load_blocked_exit_image(t_game *game);

/* ===================== Drawing ===================== */
/*
 * Functions that draw individual or grouped assets to the game window,
 * including background tiles, walls, player sprite, collectibles, etc.
 */
void	draw_background(t_game *game);
void	draw_walls(t_game *game);
void	draw_player(t_game *game);
void	draw_enemy(t_game *game);
void	draw_exit(t_game *game);
void	draw_collectibles(t_game *game);
void	draw_blocked_exit_message(t_game *game);

/* ===================== Animation ===================== */
/*
 * Handles animations for dynamic assets (e.g., collectible frame changes).
 */
void	animate_collectibles(t_game *game);
void	update_collectible_frame(t_game *game);

/* ===================== Game Loop & Events ===================== */
/*
 * Core loop function and timed updates:
 * - called continuously during gameplay
 * - handles win/loss screens and other timed logic
 */
int		game_loop(t_game *game);
int		update_enemy(void *param);

/* ===================== Cleanup ===================== */
/*
 * Frees allocated memory and destroys MLX images and windows.
 * Separates static and animated images for organized cleanup.
 */
void	cleanup(t_game *game);
void	free_static_images(t_game *game);
void	free_animated_images(t_game *game);
void	free_enemy_resources(t_game *game);
void	free_map_data(t_game *game);
void	null_all_images(t_game *game);

/* ===================== Utility ===================== */
/*
 * Helper utilities:
 * - checks file extension
 */
int		has_xpm_extension(const char *filename);
void	render(t_game *game);

#endif
