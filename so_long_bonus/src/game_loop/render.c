/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:36:38 by vhacman           #+#    #+#             */
/*   Updated: 2025/04/11 15:36:38 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
** render_moves:
** - Converts game->moves (int) to a string using ft_itoa().
** - Creates a new string by prefixing "Moves: " to the move count.
** - Draws the move count text on the window three times:
**   at (10,10), (11,10), and (10,11) pixels to produce a shadow effect,
**   improving readability against varied backgrounds.
** - Uses mlx_string_put() to render text directly on the MLX window.
** - Frees both temporary strings (number and message) after drawing
**   to prevent memory leaks.
*/
static void	render_moves(t_game *game)
{
	char	*str;
	char	*msg;

	str = ft_itoa(game->moves);
	msg = ft_strjoin("Moves: ", str);
	mlx_string_put(game->mlx, game->window, 10, 10, 0x000000, msg);
	mlx_string_put(game->mlx, game->window, 11, 10, 0x000000, msg);
	mlx_string_put(game->mlx, game->window, 10, 11, 0x000000, msg);
	free(str);
	free(msg);
}

/*
** render:
** - Draws the complete game frame each time it is called.
** - First draws the static background to cover the entire window.
** - Draws all wall tiles to create obstacles and borders.
** - Renders animated collectibles using animate_collectibles(),
**   updating their frame and position.
** - Draws the player sprite at its current coordinates.
** - Draws the enemy sprite at its current coordinates.
** - Draws the exit tile where the player must reach to win.
** - Overlays the current move count text by calling render_moves().
** - Displays the "exit blocked" popup message if active.
** - Ensures correct layering so that characters appear above background tiles.
** - Should be called after every game state change to update visuals.
*/
void	render(t_game *game)
{
	draw_background(game);
	draw_walls(game);
	animate_collectibles(game);
	draw_player(game);
	draw_enemy(game);
	draw_exit(game);
	render_moves(game);
	draw_blocked_exit_message(game);
}
