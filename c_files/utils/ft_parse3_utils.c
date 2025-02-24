/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:52:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/24 03:43:12 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks that the character <c> being processed is "valid"
// It also verifies that a player exists and that it is singular.
// Another check will be done to verify that spaces aren't in the map, later.
int	ft_parse3_util_check_valid_char(char c, bool *p1_f, bool *m_f)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*p1_f == false)
			(*p1_f) = true;
		else if (*p1_f == true)
			(*m_f) = true;
		return (0);
	}
	else if (c == '1' || c == '0' || c == ' ' || c == '\n')
		return (0);
	return (ERROR);
}

// This function makes it quick and easy to use gnl for map reading.
char	*ft_parse3_util_get_next_map_line(char *line, int open_fd, int *index)
{
	int 	bytes;
	char 	buffer[1];
	
	if (line)
		free(line);
	if (*index)
		(*index) = 0;
	line = get_next_line(open_fd, 0);
	ft_printf(LOGSV, "[VERBOSE][PARSE3]: Line to be checked is: %s\n", line);
	if (!line)
	{
			if (ft_util_malloc_or_eof(buffer, &bytes, open_fd) == ERROR)
				ft_printf(2, "Error\nMalloc failure\n");
			else if (!ft_util_malloc_or_eof(buffer, &bytes, open_fd))
				ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL]: EOF reached\n");
	}
	return (line);
}

// This function skips empty lines in between cardinal info and the map.
// It also verifies that a map exists and that malloc and read didnt fail.
char	*ft_parse3_util_skip_empty_lines(int open_fd)
{
	char	*line;
	int		i;
	char	buffer[1];
	int		bytes;

	line = NULL;
	line = get_next_line(open_fd, 0);
	while (line)
	{
		i = 0;
		while (line[i] && (ft_iswhitespace(line[i]) || line[i] == '\n'))
			i++;
		if (line[i] != '\0')
			return (line);
		free(line);
		line = get_next_line(open_fd, 0);
		if (!line)
		{
			if (ft_util_malloc_or_eof(buffer, &bytes, open_fd) == ERROR)
				ft_printf(2, "Error\nMalloc failure\n");
			else if (!ft_util_malloc_or_eof(buffer, &bytes, open_fd))
				ft_printf(2, "Error\nMap not found.\n");
		}
	}
	return (NULL);
}
int	ft_parse3_util_isnt_map_line(char *line)
{
	ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL]: Check if map line: %s\n", line);
	if (!line)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE3]:Found empty line\n");
		return (0);
	}
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	return (0);
}

char	*ft_parse3_util_get_map_line(int open_fd)
{
	char	*line;
	char	buffer[1];
	int		bytes;

	line = get_next_line(open_fd, 0);
	if (!line)
	{
		if (ft_util_malloc_or_eof(buffer, &bytes, open_fd) == ERROR)
			ft_printf(2, "Error\nMalloc failure\n");
	}
	while (line)
	{
		if (ft_parse3_util_isnt_map_line(line))
		{
			free(line);
			line = get_next_line(open_fd, 0);
		}
		else
			return (line);
	}
	return (NULL);
}
