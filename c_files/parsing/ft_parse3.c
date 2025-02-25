/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:16:11 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 05:14:15 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_parse3_assign_map_to_data(char **line, int open_fd, t_data *data)
{
	int		rows_count;

	ft_printf(LOGS, "[PARSE3]: Beginning map allocation/assignation %s\n", *line);
	if (!ft_util_is_whitespace_only(line))
	{
		free(*line);
		*line = NULL;
		if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
			return (get_next_line(open_fd, 1), ERROR);
	}
	ft_printf(LOGSV, "[VERBOSE][PARSE3]: Skipping whitespaces for memory allocation %s\n", *line);
	if (ft_parse3_util_skip_to_map(line, open_fd) == ERROR)
		return (ERROR);
	rows_count = 1;
	if (ft_parse3_util_alloc_map_memory(line, open_fd, data) == ERROR)
		return (ERROR);
	close(open_fd);
	// open_fd = open(data->filename, O_RDONLY);
	// if (open_fd == -1)
	// {
	// 	ft_printf(2, "Error\nCouldn't assign map values\n");
	// 	return (ERROR);
	// }
	// ft_printf(LOGSV, "[VERBOSE][PARSE3]: Skipping back to map lines for assignation\n");
	return (0);
}