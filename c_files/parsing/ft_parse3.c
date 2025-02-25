/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:16:11 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 07:25:31 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_parse3_assign_map_to_data(char **line, int open_fd, t_data *data)
{
	ft_printf(LOGS, "[PARSE3]: Beginning map allocation/assignation\n");
	ft_printf(LOGSV, "[VERBOSE][PARSE3]: Skipping whitespaces for memory allocation\n");
	if (ft_parse3_util_skip_to_map(line, open_fd) == ERROR)
		return (close(open_fd), ERROR);
	if (ft_parse3_util_alloc_map_memory(line, open_fd, data) == ERROR)
		return (close(open_fd), ERROR);
	get_next_line(open_fd, 1);
	close(open_fd);
	open_fd = open(data->filename, O_RDONLY);
	if (open_fd == -1)
	{
		ft_printf(2, "Error\nCouldn't assign map values\n");
		return (ERROR);
	}
	*line = NULL;
	ft_printf(LOGSV, "[VERBOSE][PARSE3]: Skipping back to map lines for assignation\n");
	if (ft_parse3_util_skip_to_map(line, open_fd) == ERROR)
		return (ERROR);
	if (ft_parse3_util2_initialize_map(line, open_fd, data) == ERROR)
		return (ERROR);
	while (*line && !ft_util_is_whitespace_only(line))
	{
		if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
			return (get_next_line(open_fd, 1), close(open_fd), ERROR);
	}
	if (*line && ft_util_is_whitespace_only(line) == ERROR)
	{
		free(*line);
		get_next_line(open_fd, 1);
		close(open_fd);
		return (ft_printf(2, "Error\nFound duplicate map\n"), ERROR);
	}
	return (get_next_line(open_fd, 1), close(open_fd), free(*line), 0);
}
