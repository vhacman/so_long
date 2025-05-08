/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:44:36 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/16 14:44:36 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Displays the appropriate end screen image (win or loss).
 * - Uses a static reference timestamp game->win_time.
 * - Computes elapsed time in milliseconds since game ended.
 * - Calculates screen center using image and window dimensions.
 * - Draws either win or loss image using mlx_put_image_to_window().
 * - After 2000ms, calls handle_destroy() to exit the game cleanly.
 */
static void	draw_end_screen(t_game *game, int won, struct timeval current_time)
{
	long	elapsed_ms;
	int		center_x;
	int		center_y;

	elapsed_ms = (current_time.tv_sec - game->win_time.tv_sec) * 1000;
	elapsed_ms += (current_time.tv_usec - game->win_time.tv_usec) / 1000;
	if (won)
	{
		center_x = (game->window_width - game->img_win_width) / 2;
		center_y = (game->window_height - game->img_win_height) / 2;
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_win, center_x, center_y);
	}
	else
	{
		center_x = (game->window_width - game->img_lost_width) / 2;
		center_y = (game->window_height - game->img_lost_height) / 2;
		mlx_put_image_to_window(game->mlx, game->window,
			game->img_lost, center_x, center_y);
	}
	if (elapsed_ms > 2000)
		handle_destroy(game);
}

/*
 * Moves the enemy along a predefined path stored in enemy_path.
 * - Saves previous x-position to determine movement direction.
 * - If path index is valid, updates enemy position and increments index.
 * - If path is completed, resets index to 0 to loop animation.
 * - Sets game->enemy_dir based on horizontal movement direction:
 *   1 if moving right, -1 if moving left.
 */
static void	move_enemy(t_game *game)
{
	int	prev_x;

	prev_x = game->enemy_x;
	if (game->enemy_path_index < game->enemy_path_len)
	{
		game->enemy_x = game->enemy_path[game->enemy_path_index].x;
		game->enemy_y = game->enemy_path[game->enemy_path_index].y;
		game->enemy_path_index++;
	}
	else
		game->enemy_path_index = 0;
	if (game->enemy_x > prev_x)
		game->enemy_dir = 1;
	else if (game->enemy_x < prev_x)
		game->enemy_dir = -1;
}

/*
 * Checks for collision between enemy and player.
 * - Compares enemy and player coordinates.
 * - If matched, sets game->lost = 1 and records win_time.
 * - Prints "Game over." and returns 1 to indicate collision.
 * - Returns 0 if no collision occurred.
 */
static int	handle_collision(t_game *game)
{
	if (game->enemy_x == game->player_x && game->enemy_y == game->player_y)
	{
		ft_printf("Game over.\n");
		game->lost = 1;
		gettimeofday(&game->win_time, NULL);
		return (1);
	}
	return (0);
}

/*
 * Periodic enemy update routine for MLX loop hook.
 * - Casts param to t_game pointer to access game state.
 * - If game is over (won/lost), calls draw_end_screen().
 * - Measures elapsed time since last enemy move using static timeval.
 * - Skips update if < 300ms elapsed to regulate movement speed.
 * - Otherwise, updates enemy position, re-renders screen,
 *   and checks for player collision.
 * - Always returns 0 as required by MLX loop.
 */
int	update_enemy(void *param)
{
	t_game					*game;
	struct timeval			current_time;
	static struct timeval	last_move = {0};
	long					elapsed_ms;

	game = (t_game *)param;
	gettimeofday(&current_time, NULL);
	if (game->won || game->lost)
	{
		draw_end_screen(game, game->won, current_time);
		return (0);
	}
	elapsed_ms = (current_time.tv_sec - last_move.tv_sec) * 1000;
	elapsed_ms += (current_time.tv_usec - last_move.tv_usec) / 1000;
	if (elapsed_ms < 300)
		return (0);
	last_move = current_time;
	move_enemy(game);
	render(game);
	handle_collision(game);
	return (0);
}
