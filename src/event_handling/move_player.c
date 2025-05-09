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
** Checks whether the target coordinates (new_x, new_y) fall within
** the valid boundaries of the map.
** - Rejects moves that are negative or exceed map dimensions.
**
** Parameters:
** - game: pointer to the game structure with map metadata.
** - new_x: target x-coordinate.
** - new_y: target y-coordinate.
**
** Return:
** - 1 if the position is valid, 0 if out of bounds.
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
** Evaluates the result of stepping onto a given map tile.
** - '1' → wall: movement blocked.
** - 'C' → collectible: decrement collectible counter.
** - 'E' → exit:
**     - If all collectibles are collected, set win state.
**     - If not, trigger blocked-exit message (only once).
**
** Parameters:
** - game: pointer to the game structure.
** - tile: character at the destination tile.
**
** Return:
** - 1 if movement is allowed, 0 if blocked.
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
			game->win_screen_shown = 0;
			game->win_screen_counter = 0;
			return (1);
		}
		else
		{
			if (!game->blocked_msg_shown)
			{
				game->blocked_msg_shown = 1;
				game->blocked_msg_counter = 0;
			}
			return (0);
		}
	}
	return (1);
}

/*
** Checks whether the attempted move is legal.
** - Verifies that the target tile is in bounds and not blocked.
** - Applies tile-specific logic via handle_tile_effects().
**
** Parameters:
** - game: pointer to the game structure.
** - new_x: target x-coordinate.
** - new_y: target y-coordinate.
**
** Return:
** - 1 if the move is allowed, 0 otherwise.
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
** Updates the player's position and internal game state.
** - Applies direction based on dx to control sprite orientation.
** - Replaces old tile with '0' unless it was an 'E'.
** - Replaces new tile with 'P' unless it's an 'E'.
** - Increments move counter and prints total to stdout.
**
** Parameters:
** - game: pointer to the game structure.
** - dx: delta x for movement direction.
** - dy: delta y for movement direction.
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
** Performs player movement after input.
** - Computes new coordinates from dx/dy.
** - If the move is valid, updates player state and map.
** - Always triggers a redraw of the game window.
**
** Parameters:
** - game: pointer to the game structure.
** - dx: horizontal movement offset.
** - dy: vertical movement offset.
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
