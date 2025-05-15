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
 ** check_bounds_and_enemy:
 ** Checks if new_x and new_y are inside map limits.
 ** If out of bounds, returns 0 (invalid move).
 ** If coordinates match enemy's position:
 **   - Prints "Game over."
 **   - Sets game->lost to 1.
 **   - Records current time in game->win_time.
 **   - Returns 0 (invalid move).
 ** Otherwise, returns 1 (valid move).
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
 ** handle_tile_effects:
 ** Processes the effect of stepping on a tile.
 ** If tile is '1' (wall), blocks move (returns 0).
 ** If tile is 'C' (collectible), decreases collectible count.
 ** If tile is 'E' (exit):
 **   - If all collectibles collected:
 **       - Prints "YOU WON"
 **       - Sets game->won to 1
 **       - Records current time in game->win_time
 **       - Allows move (returns 1).
 **   - Else:
 **       - If blocked message not shown:
 **           - Records current time for message timing.
 **           - Sets blocked_msg_shown flag.
 **       - Blocks move (returns 0).
 ** Otherwise, returns 1 (move allowed).
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
 ** is_valid_move:
 ** Checks if new position is within bounds and not on enemy.
 ** Checks tile effects using handle_tile_effects.
 ** Returns 1 if move allowed, 0 if blocked by bounds or tile logic.
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
 ** update_player_position:
 ** Updates player's x and y by dx and dy.
 ** Updates player direction: 1 if moving right, -1 if left.
 ** Clears old position tile unless it is an exit.
 ** Sets new position tile to 'P' unless it is an exit.
 ** Increments move count.
 ** Prints current move count to stdout.
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
 ** move_player:
 ** Computes new target position from current pos + dx/dy.
 ** Calls is_valid_move to check legality of move.
 ** If invalid, calls render() without moving.
 ** If valid:
 **   - Calls update_player_position.
 **   - Checks if player is on exit with no collectibles:
 **       - Prints "YOU WON"
 **       - Sets game->won to 1
 **       - Records current time in game->win_time.
 **   - Calls update_enemy to move enemy after player.
 **   - Calls render() to update display.
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
