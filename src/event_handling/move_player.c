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
** Processes the effect of stepping onto a map tile and determines if
** movement is allowed.
**
** - If the tile is a wall ('1'), movement is blocked and returns 0.
** - If the tile is a collectible ('C'), decreases the collectible
**   counter (player picks it up).
** - If the tile is the exit ('E'):
**     - If all collectibles have been gathered, the player wins:
**         - Sets the win flag to 1.
**         - Resets win screen state to allow rendering.
**         - Prints a victory message.
**         - Returns 1 to allow movement onto the tile.
**     - If not all collectibles are collected:
**         - Blocks the movement (returns 0).
**         - Triggers a one-time message to inform the player that the
**           exit is not yet accessible (controlled by a flag and counter).
**
** Parameters:
** - game: Pointer to the main game structure, which tracks game state,
**   collectibles, exit condition, and messages.
** - tile: Character representing the type of tile the player is stepping on.
**
** Return:
** - Returns 1 if movement onto the tile is allowed.
** - Returns 0 if movement is blocked (wall or incomplete exit).
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
** Updates the player's position and modifies the game state accordingly.
**
** - Calculates the new coordinates using the given dx/dy values.
** - Updates player sprite direction based on horizontal movement:
**     dx > 0 → facing right (1), dx < 0 → facing left (-1).
** - Replaces the previous tile with '0' (empty) only if it wasn't 'E'
**   (exit), to preserve the exit symbol on the map.
** - Updates the player's coordinates in the game structure.
** - Replaces the new tile with 'P' (player) unless it's an 'E',
**   allowing the player to stand on the exit without overwriting it.
** - Increments the move counter and prints the total number of moves
**   to the standard output using ft_printf.
**
** Parameters:
** - game: Pointer to the main game structure holding player state,
**   map, direction, and move count.
** - dx: Horizontal movement offset: -1 (left), +1 (right), or 0 (none).
** - dy: Vertical movement offset: -1 (up), +1 (down), or 0 (none).
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
** Handles the player's movement based on keyboard input.
**
** - Calculates the new target position by applying dx and dy
**   to the player's current coordinates.
** - Checks if the destination cell is walkable using is_valid_move.
** - If the move is valid, updates the player position and map state.
** - Always redraws the game window, even if the move is invalid.
**
** Parameters:
** - game: Pointer to the main game structure containing the map,
**   player position, and other game state.
** - dx: Horizontal movement direction.
**       Use -1 to move left, +1 to move right, 0 for no horizontal move.
** - dy: Vertical movement direction.
**       Use -1 to move up, +1 to move down, 0 for no vertical move.
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
