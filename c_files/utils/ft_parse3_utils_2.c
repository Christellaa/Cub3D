/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:13:05 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 07:19:36 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_parse3_util2_initialize_map(char **line, int open_fd, t_data *data)
{
	int	i;

	i = 0;
	if (*line)
	{
		while (*line && ft_util_is_whitespace_only(line) == ERROR && i < data->map->rows)
		{
			data->map->map[i] = ft_strdup(*line);
			if (!data->map->map[i])
			{
				ft_printf(2, "Error\nMalloc error in map initialization\n");
				return (get_next_line(open_fd, 1), ERROR);
			}
			if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
				return (get_next_line(open_fd, 1), ERROR);
			ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL2]: assigned %s\n", data->map->map[i]);
			i++;
		}
	}
	data->map->map[i] = NULL;
	ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL2]: assigned %s\n", data->map->map[i]);
	return (0);
}
