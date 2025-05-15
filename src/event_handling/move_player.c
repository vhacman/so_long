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
** handle_tile_effects:
** - Interprets the content of the destination tile and determines if
**   the player can move there.
** - If tile is '1' (wall), movement is blocked.
** - If tile is 'C' (collectible), decrements the collectible counter.
** - If tile is 'E' (exit):
**     - If all collectibles are collected:
**         - Sets win state flags.
**         - Prints "YOU WON".
**         - Allows movement.
**     - Otherwise:
**         - Blocks movement.
**         - Triggers one-time "exit blocked" message.
** - Returns 1 if movement is allowed, 0 if blocked.
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
** is_valid_move:
** - Determines if a move to (new_x, new_y) is allowed.
** - First checks that the coordinates are within bounds.
** - Then applies logic specific to the tile using handle_tile_effects.
** - Returns 1 if move is valid, otherwise 0.
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
** Update_player_position:
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
** move_player:
** - Handles the movement attempt of the player by applying a directional
**   offset (dx, dy) to the current position.
**
** - Computes new_x and new_y by adding dx and dy to the player's current
**   coordinates (game->player_x, game->player_y).
**
** - Calls is_valid_move to check if movement to (new_x, new_y) is allowed:
**     - If the move is invalid (out of bounds, wall, blocked exit), the
**       function skips movement and proceeds to redraw the window.
**
** - If the move is valid:
**     - Calls update_player_position to apply changes (position and map state).
**
** - Regardless of move validity, calls render() at the end to refresh
**   the entire window, ensuring the display is up to date after each input.
**
** - The function does not itself modify player coordinates or the map; it
**   delegates that logic to update_player_position if the move is valid.
**
** Parameters:
** - game: Pointer to the game structure containing player position and
**         overall game state.
** - dx: Horizontal offset to apply to player_x (e.g., -1 = left, 1 = right).
** - dy: Vertical offset to apply to player_y (e.g., -1 = up, 1 = down).
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
