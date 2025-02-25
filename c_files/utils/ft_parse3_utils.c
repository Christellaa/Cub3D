/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:18:05 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 07:16:48 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_parse3_util_skip_whitespaces(char **line, int open_fd)
{
	while (ft_util_is_whitespace_only(line) != ERROR)
	{
		if (ft_util_safe_gnl(line, open_fd, 0) == 1)
		{
			ft_printf(2, "Error\nMap not found\n");
			return (get_next_line(open_fd, 1), ERROR);
		}
		if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
			return (get_next_line(open_fd, 1), ERROR);
	}
	return (0);
}

int	ft_parse3_util_skip_to_map(char **line, int open_fd)
{
	int	gnl_return;
	
	if (*line && (*line)[0] != '\0' && ft_util_is_whitespace_only(line) == ERROR)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL]: Started on first line of map %s\n", *line);
		return (0);
	}
	if (*line)
		free(*line);
	*line = NULL;
	if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
		return (get_next_line(open_fd, 1), ERROR);
	while (ft_parse3_util_skip_one(*line))
	{
		gnl_return = ft_util_safe_gnl(line, open_fd, 0);
		if (gnl_return == ERROR)
			return (get_next_line(open_fd, 1), ERROR);
		if (gnl_return == 1)
		{
			ft_printf(2, "Error\nMap not found\n");
			return (get_next_line(open_fd, 1), ERROR);
		}
	}
	ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL]: Found first line of map: %s\n", *line);
	return (0);
}

int	ft_parse3_util_skip_one(char *line)
{
	int	index;

	index = 0;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2))
		return (1);
	if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (1);
	while (line[index])
	{
		if (ft_iswhitespace(line[index]) || line[index] == '\n')
			index++;
		else
			break ;
	}
	if (line[index] == '\n' || line[index] == '\r' || line[index] == '\0')
		return (1);
	return (0);
}

int	ft_parse3_util_alloc_map_memory(char **line, int fd, t_data *data)
{
	ft_printf(LOGSV, "[VERBOSE][PARSE3]: Allocating memory for char **map\n");
	while (*line && ft_util_is_whitespace_only(line) == ERROR)
	{
		if (ft_parse3_util_is_invalid_line(line))
		{
			ft_printf(2, "Error\nInvalid line detected %s\n", *line);
			free(*line);
			return (get_next_line(fd, 1), ERROR);
		}
		data->map->rows += 1;
		if (ft_util_safe_gnl(line, fd, 0) == ERROR)
		{
			free(*line);
			return (get_next_line(fd, 1), ERROR);
		}
	}
	data->map->map = (char **)malloc(sizeof(char *) * (data->map->rows + 1));
	free(*line);
	get_next_line(fd, 1);
	if (!data->map->map)
		return (ft_printf(2, "Error\nMalloc failure\n"), ERROR);
	return (0);
}

int	ft_parse3_util_is_invalid_line(char **line)
{
	int i;
	char	*temp;
	
	temp = ft_strdup(*line);
	i = 0;
	while (temp[i])
	{
		if (temp[i] != '1' && temp[i] != '0' && temp[i] != ' '
			&& temp[i] != 'N' && temp[i] != 'S' && temp[i] != 'E'
			&& temp[i] != 'W')
			{
				return (free(temp), ERROR);
			}
		i++;
	}
	free(temp);
	return (0);
}