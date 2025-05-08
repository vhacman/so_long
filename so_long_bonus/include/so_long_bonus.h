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

/* ===================== Key Codes & Constants ===================== */
/*
 * Keycodes for standard input handling. These values are used to detect
 * user interactions with the keyboard for movement and quitting.
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

/* ===================== Standard & Custom Libraries ===================== */
/*
 * Included libraries:
 * - mlx: minimal X window graphics library
 * - stdlib, unistd, fcntl: standard system-level functions
 * - libft: custom utility library (string/memory/print functions)
 * - get_next_line: utility to read map files line by line
 * - sys/time.h: used for measuring time intervals (animations, delays)
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
 * Simple coordinate structure used for tracking 2D positions or directions.
 */
typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

/*
 * The main game structure.
 * It holds:
 * - rendering context (mlx, window)
 * - map layout and size
 * - player position and graphics
 * - enemy position, behavior, and path memory
 * - collectible animations
 * - win/loss/intro screen data
 * - counters and flags for game progression and state
 */
typedef struct s_game
{
	/* MLX graphical context and window properties */
	void			*mlx;
	void			*window;
	int				window_width;
	int				window_height;

	/* Map and its dimensions */
	char			**map;
	int				map_width;
	int				map_height;

	/* Player information and movement tracking */
	int				player_x;
	int				player_y;
	int				player_direction;
	int				collectibles;
	int				moves;
	void			*img_player_right;
	void			*img_player_left;

	/* Background, wall, and exit images */
	void			*img_background;
	void			*img_wall;
	void			*img_exit;

	/* Enemy data: position, direction, path memory */
	void			*img_enemy_right;
	void			*img_enemy_left;
	int				enemy_x;
	int				enemy_y;
	int				enemy_dx;
	int				enemy_dy;
	int				enemy_dir;
	t_point			*enemy_path;
	int				enemy_path_len;
	int				enemy_path_index;
	int				**visited;

	/* Animated collectibles (4-frame cycle) */
	void			*img_collectibles[4];
	int				collectible_frame;

	/* Game status: win/loss flags and timers */
	int				won;
	int				lost;
	struct timeval	win_time;
	void			*img_win;
	void			*img_lost;
	int				img_win_width;
	int				img_win_height;
	int				img_lost_width;
	int				img_lost_height;

	/* Intro screen image and its state */
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
/* Program entry function declared in main.c */
int		main(int argc, char **argv);

/* ===================== Initialization ===================== */
/*
 * Functions responsible for setting up the game:
 * - creating the window
 * - loading and validating the map
 * - handling errors
 */
void	init_window(t_game *game, int width, int height, char *title);
void	load_map(t_game *game, char *filename);
void	clean_map(t_game *game);
void	validate_map(t_game *game);
int		validate_path(t_game *game);
void	exit_with_error(char *msg, t_game *game, int flag);

/* ===================== Map Validation ===================== */
/*
 * Validates that the map:
 * - contains valid characters
 * - is rectangular and properly enclosed by walls
 * - has all required components
 * - has a valid path from start to collectibles and exit
 */
int		is_valid_char(char c);
void	check_characters(t_game *game, int *p_count,
			int *e_count, int *c_count);
void	check_rectangular_and_walls(t_game *game);
int		check_remaining_elements(char **map_copy, int map_height);
void	free_map_copy(char **map_copy, int map_height);

/* ===================== Input Handling ===================== */
/*
 * Manages keyboard and window events:
 * - movement (WASD / arrow keys)
 * - exiting (ESC / window close)
 */
int		handle_key(int key, t_game *game);
int		handle_destroy(t_game *game);
void	move_player(t_game *game, int dx, int dy);

/* ===================== Asset Loading ===================== */
/*
 * Loads .xpm assets into memory for rendering:
 * - background, walls, player, enemy, exit, collectibles, win/lost screens
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
 * Handles drawing game components on the screen:
 * - background, walls, characters, collectibles, exit
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
 * Handles animation logic for assets that change over time:
 * - collectibles animated in cycles
 */
void	animate_collectibles(t_game *game);
void	update_collectible_frame(t_game *game);

/* ===================== Game Loop ===================== */
/*
 * Functions called by MLX at each frame:
 * - game_loop handles time-based events (e.g. win delay)
 * - update_enemy moves the enemy at intervals
 */
int		game_loop(t_game *game);
int		update_enemy(void *param);

/* ===================== Enemy Pathfinding ===================== */
/*
 * Functions related to enemy AI:
 * - calculating movement path
 * - initializing memory for path tracking
 */
void	spawn_enemy(t_game *game);
void	init_enemy_path(t_game *game, int x, int y);

/* ===================== Cleanup ===================== */
/*
 * Frees dynamically allocated memory and MLX images:
 * - called on exit or error
 */
void	cleanup(t_game *game);
void	free_static_images(t_game *game);
void	free_animated_images(t_game *game);
void	free_enemy_resources(t_game *game);
void	free_map_data(t_game *game);
void	null_all_images(t_game *game);

/* ===================== Utility ===================== */
/* Checks if a file path ends in ".xpm" */
int		has_xpm_extension(const char *filename);
void	render(t_game *game);

#endif
