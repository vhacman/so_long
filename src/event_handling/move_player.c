/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 23:35:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/08 23:35:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Checks whether the destination coordinates are within map bounds.
 * - Returns 0 if new_x or new_y are negative or exceed map size.
 * - Ensures the player does not access invalid memory or leave the map.
 */
static int	check_bounds(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0)
		return (0);
	if (new_x >= game->map_width || new_y >= game->map_height)
		return (0);
	return (1);
}

/*
 * Handles interactions with the destination tile:
 * - '1': wall → movement is blocked, returns 0.
 * - 'C': collectible → decrements collectible counter.
 * - 'E': exit → if collectibles == 0, triggers win state:
 *     - Sets game->won = 1.
 *     - Calls gettimeofday(&game->win_time, NULL) to record the
 *       current system time in microseconds.
 *       This timestamp is used later to measure delay before quitting.
 *   → If collectibles remain, blocks movement and sets
 *     game->blocked_msg_shown = 1 to trigger a one-time message,
 *     recording the time in game->blocked_msg_time with gettimeofday().
 * - Returns 1 if movement is allowed, 0 otherwise.
 */
static int	handle_tile_effects(t_game *game, char tile)
{
	if (tile == '1')
		return (0);
	if (tile == 'C')
		game->collectibles--;
	if (tile == 'E')
	{
		if (game->collectibles == 0)
		{
			ft_printf("YOU WON\n");
			game->won = 1;
			gettimeofday(&game->win_time, NULL);
			return (1);
		}
		else
		{
			if (!game->blocked_msg_shown)
			{
				gettimeofday(&game->blocked_msg_time, NULL);
				game->blocked_msg_shown = 1;
			}
			return (0);
		}
	}
	return (1);
}

/*
 * Validates the legality of the target move.
 * - Checks boundary constraints and tile interaction rules.
 * - Returns 1 if the move is valid and allowed.
 * - Returns 0 if the move is out of bounds or blocked.
 */
static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (!check_bounds(game, new_x, new_y))
		return (0);
	if (!handle_tile_effects(game, game->map[new_y][new_x]))
		return (0);
	return (1);
}

/*
 * Updates the player's map position and state.
 * - dx/dy indicate movement direction on x and y axes.
 * - Sets direction (1 for right, -1 for left) to adjust sprite rendering.
 * - Previous tile is reset to '0' unless it's an exit tile.
 * - New tile is marked as 'P' unless it's an exit tile.
 * - Increments and prints the total number of moves.
 */
static void	update_player_position(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (dx > 0)
		game->player_direction = 1;
	if (dx < 0)
		game->player_direction = -1;
	if (game->map[game->player_y][game->player_x] != 'E')
		game->map[game->player_y][game->player_x] = '0';
	game->player_x = new_x;
	game->player_y = new_y;
	if (game->map[new_y][new_x] != 'E')
		game->map[new_y][new_x] = 'P';
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
}

/*
 * Processes player movement on input.
 * - Computes target position using dx/dy offset.
 * - Validates move legality via is_valid_move().
 * - If valid, updates state and triggers a redraw with render().
 */
void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_move(game, new_x, new_y))
	{
		render(game);
		return ;
	}
	update_player_position(game, dx, dy);
	render(game);
}
