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
** count_line:
** - Opens the file at the given path in read-only mode.
** - Reads the file line by line using get_next_line.
** - For each line read:
**     - Increments the line counter.
**     - Frees the line to prevent memory leaks.
** - After reading, closes the file and returns the total number of lines.
** - If the file cannot be opened (open returns -1), returns -1.
** - Used to determine the number of rows in the map (map height).
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
** load_map:
** - Loads a textual map file into memory and stores it in game->map.
** - First, uses count_line to determine how many lines are in the file
**   and stores the value in game->map_height.
** - Allocates memory for a NULL-terminated array of strings
**   with ft_calloc (one extra for the NULL terminator).
** - Opens the map file again in read-only mode.
** - Reads each line with get_next_line, duplicates it with ft_strdup,
**   and stores it in the map array. Frees the original line.
** - After all lines are read:
**     - Closes the file descriptor.
**     - Sets game->map[i] = NULL to mark the end of the array.
**     - Sets game->map_width using the length of the first row.
** - If file reading fails at any point (file not found, empty, or malloc
**   failure), exits the program with an appropriate error message.
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
