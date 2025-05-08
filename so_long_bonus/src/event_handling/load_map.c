/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:31:50 by vhacman           #+#    #+#             */
/*   Updated: 2025/05/09 15:31:50 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/*
 * Counts the number of lines in a map file.
 * - Opens the file in read-only mode and reads line by line.
 * - Increments a counter for each line read using get_next_line().
 * - Frees each line after reading to avoid memory leaks.
 * - Closes the file and returns the total number of lines.
 * - Returns -1 if the file cannot be opened, indicating error.
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
 * Loads the map from a file into the game struct.
 * - Validates the file and counts its lines to determine map height.
 * - Allocates memory for the map based on the number of lines.
 * - Reads each line, duplicates it, and stores it in the map array.
 * - Sets the map width using the length of the first line.
 * - Exits with an error if file is invalid, unreadable, or empty.
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
