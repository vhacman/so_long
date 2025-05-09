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
** Counts the number of lines in the given map file.
** - Opens the file in read-only mode.
** - Reads the file line by line using get_next_line().
** - Frees each line after reading to avoid memory leaks.
** - Closes the file and returns the number of lines read.
** - Returns -1 if the file cannot be opened.
**
** Parameters:
** - filename: path to the map file to be analyzed.
**
** Return:
** - Total number of lines (rows) in the map, or -1 on error.
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
** Loads a map file into the game's internal map structure.
** - Determines the map height using count_line().
** - Allocates a NULL-terminated array of strings for the map.
** - Opens the file and reads each line, duplicating it with ft_strdup().
** - Each line is freed after duplication.
** - The map is stored in game->map, with map height and width set.
** - If the file is missing, unreadable, or empty, terminates with error.
**
** Parameters:
** - game: pointer to the game structure where map data will be stored.
** - filename: path to the map file to be loaded.
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
