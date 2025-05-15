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
** Draws the win or loss screen centered in the window.
** Calculates milliseconds elapsed since game ended.
** Shows win image if player won, loss image if lost.
** After 2000 ms, calls handle_destroy() to exit cleanly.
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
** The function move_enemy updates the enemy’s position along a 
** predefined path step by step. It works as follows:
** It saves the enemy’s current horizontal position (prev_x).
**
** It checks if the enemy still has steps left in its path 
** (enemy_path_index < enemy_path_len).
** If yes, it updates the enemy’s coordinates (enemy_x, enemy_y) 
** to the next point on the path.
**
** Then it increments the path index to move to 
** the next step for the next call.
**
** If the enemy has reached the end of the path, 
** it resets the path index to 0, so the enemy repeats the path from the start.
** After moving, it compares the new horizontal 
** position (enemy_x) to the old one (prev_x):
**
** If enemy_x is greater than prev_x, the enemy moved right,
** so enemy_dir is set to 1.
**
** If enemy_x is less than prev_x, the enemy moved left, 
** so enemy_dir is set to -1.
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
** Checks if the enemy and player occupy the same position (collision).
** - Compares enemy_x and enemy_y with player_x and player_y coordinates.
** - If they match, the player has been caught by the enemy.
** - On collision:
**   - Prints "Game over." to the console.
**   - Sets game->lost to 1 to indicate the player lost.
**   - Records the current time in game->win_time to manage game end.
**   - Returns 1 to signal a collision occurred.
** - Returns 0 if no collision is detected.
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
** Periodic function called by the MLX loop to update the enemy.
** - Casts the generic pointer to t_game* to access game state.
** - Retrieves the current time using gettimeofday().
** - If the game is won or lost, draws the end screen and stops updating.
** - Calculates elapsed time in milliseconds since the enemy last moved.
** - If less than 300 ms have passed, skips the update to slow movement.
** - Otherwise, moves the enemy along its path.
** - Calls render() to redraw the screen with updated positions.
** - Checks for collision between enemy and player.
** - Always returns 0 as required by MLX hook functions.
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
