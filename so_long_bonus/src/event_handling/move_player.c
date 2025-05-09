/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:16:21 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 12:16:21 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Checks if the new player position is valid and safe.
 * - Verifies that new_x and new_y are within map boundaries.
 * - If the destination is the enemy’s location, sets game->lost to 1
 *   and records the current time using gettimeofday().
 * - Prevents out-of-bounds access or invalid enemy collisions.
 * - Returns 1 if the move is allowed, 0 otherwise.
 */
static int	check_bounds_and_enemy(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_y < 0)
		return (0);
	if (new_x >= game->map_width || new_y >= game->map_height)
		return (0);
	if (new_x == game->enemy_x && new_y == game->enemy_y)
	{
		ft_printf("Game over.\n");
		game->lost = 1;
		gettimeofday(&game->win_time, NULL);
		return (0);
	}
	return (1);
}

/*
 * Processes the effects of stepping on a map tile.
 * - Blocks movement into walls ('1').
 * - If the tile is a collectible ('C'), decrements collectible count.
 * - If the tile is an exit ('E') and all collectibles are collected,
 *   sets game->won to 1 and records the win time.
 * - Does not block exit if it's the winning condition; otherwise, blocks.
 * - Returns 1 if the move can proceed, 0 if blocked.
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
 * Validates a move using positional and tile checks.
 * - Uses check_bounds_and_enemy() to verify coordinates are legal.
 * - Uses handle_tile_effects() to enforce map tile logic.
 * - Prevents invalid or game-ending moves from executing.
 * - Returns 1 if the move is valid; 0 otherwise.
 */
static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	char	tile;

	if (!check_bounds_and_enemy(game, new_x, new_y))
		return (0);
	tile = game->map[new_y][new_x];
	if (!handle_tile_effects(game, tile))
		return (0);
	return (1);
}

/*
 * Updates the player’s position on the map and modifies game state.
 * - dx and dy are relative displacements on the x and y axes.
 *   Example: (dx = 1, dy = 0) moves the player one step right.
 * - Updates player direction: 1 for right, -1 for left.
 * - Replaces previous tile with '0' unless it was an exit ('E').
 * - Updates new tile with 'P' unless it’s an exit.
 * - Increments move counter and prints total moves to stdout.
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
 * Controls player movement based on directional input.
 * - dx and dy define the intended move direction.
 *   dx = ±1: horizontal movement; dy = ±1: vertical movement.
 *   (dx = 0, dy = -1) → up; (dx = 0, dy = 1) → down
 *   (dx = -1, dy = 0) → left; (dx = 1, dy = 0) → right
 * - Validates the move and updates player position if allowed.
 * - Checks if player reached exit with no collectibles to win.
 * - Updates enemy position and re-renders the game view.
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
	if (game->map[game->player_y][game->player_x] == 'E'
		&& game->collectibles == 0)
	{
		ft_printf("YOU WON\n");
		game->won = 1;
		gettimeofday(&game->win_time, NULL);
	}
	update_enemy(game);
	render(game);
}
