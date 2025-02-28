/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:16:11 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/28 03:48:19 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function skips to the map using the the line at the start of file
// It then allocates memory for the entire map
// It skips back to the start of the map.
// And initializes the whole map with strduping.
// It then verifies that there is only one map.
// Returns 0 on success, ERROR on failure
int	ft_parse3_assign_map_to_data(char **line, int open_fd, t_data *data)
{
	if (ft_parse3_util_skip_to_map(line, open_fd) == ERROR)
		return (close(open_fd), ERROR);
	if (ft_parse3_util_alloc_map_memory(line, open_fd, data) == ERROR)
		return (close(open_fd), ERROR);
	get_next_line(open_fd, 1);
	close(open_fd);
	open_fd = open(data->filename, O_RDONLY);
	if (open_fd == -1)
		return (ft_printf(2, "Error\nCouldn't assign map values\n"), ERROR);
	*line = NULL;
	if (ft_parse3_util_skip_to_map(line, open_fd) == ERROR)
		return (close(open_fd), ERROR);
	if (ft_parse3_util2_initialize_map(line, open_fd, data) == ERROR)
		return (close(open_fd), ERROR);
	while (*line && !ft_util_is_whitespace_only(line))
	{
		if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
			return (get_next_line(open_fd, 1), close(open_fd), ERROR);
	}
	if (*line && ft_util_is_whitespace_only(line) == ERROR)
	{
		ft_printf(2, "Error\nFound duplicate map\n");
		return (free(*line), get_next_line(open_fd, 1), close(open_fd), ERROR);
	}
	return (get_next_line(open_fd, 1), close(open_fd), free(*line), 0);
}

// This function verifies the existence of a singular player within <data>
// Then using the map found in data, it verifies that the map is closed.
int	ft_parse3_flood_fill(t_data *data)
{
	ft_printf(LOGS, "[PARSE3]: Checking singular player\n");
	if (ft_parse3_util2_single_player(data) == ERROR)
		return (ERROR);
	if (ft_parse3_util2_check_map_closed(data->map) == ERROR)
		return (ERROR);
	data->player->pos_x = (double)data->map->map_x;
	data->player->pos_y = (double)data->map->map_y;
	return (0);
}
