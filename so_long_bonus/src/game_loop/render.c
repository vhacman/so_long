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
 * Displays the current number of player moves on screen.
 * - Converts game->moves (int) to a string using ft_itoa().
 * - Creates a new string by concatenating "Moves: " with the move count.
 * - Draws the resulting message three times with slight pixel offsets
 *   to create a shadow or bold effect for better readability.
 * - Uses mlx_string_put() to draw directly onto the game window.
 * - Frees both allocated strings after drawing to avoid memory leaks.
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
 * Draws the full game frame in the correct layer order.
 * - Begins with the background, followed by static elements like walls.
 * - Calls animate_collectibles() to render collectibles with animation.
 * - Then draws player, enemy, and exit so they appear above the base tiles.
 * - Finally, calls render_moves() to overlay the move count on top.
 * - This function is called after every state update to refresh display.
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
