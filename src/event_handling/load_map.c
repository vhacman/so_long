/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:31:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/08 15:31:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
 * Counts the number of lines in the map file.
 * - Opens the file in read-only mode using open().
 * - Uses get_next_line() to read one line at a time.
 * - Increments a counter for each successfully read line.
 * - Frees each line to avoid memory leaks.
 * - Closes the file at the end.
 * - Returns the number of lines found (used as map height).
 * - If file cannot be opened, returns -1 to indicate error.
 */
static int	count_line(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	return (lines);
}

/*
 * Loads the map from file into game->map (2D array of strings).
 * - First, count_line() is called to get the number of rows.
 * - Allocates memory for the map array (height + 1 for NULL terminator).
 * - Opens the map file a second time in read-only mode.
 * - Uses get_next_line() to read each line into map[i].
 * - Each line is duplicated with ft_strdup() to manage memory safely.
 * - The line read is freed immediately after duplication.
 * - After all lines are read, the map array is NULL-terminated.
 * - game->map_width is set using the length of the first row.
 * - If file is invalid, unreadable, or empty, exits with error.
 */
void	load_map(t_game *game, char *filename)
{
	int		fd;
	int		i;
	char	*line;

	game->map_height = count_line(filename);
	if (game->map_height <= 0)
		exit_with_error("Error\nEmpty or invalid map file\n", game, 0);
	game->map = ft_calloc(game->map_height + 1, sizeof(char *));
	if (!game->map)
		exit_with_error("Error\nMemory allocation failed for map\n", game, 0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_with_error("Error\nMap file not found\n", game, 0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->map[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	close (fd);
	game->map_width = ft_strlen(game->map[0]);
}
