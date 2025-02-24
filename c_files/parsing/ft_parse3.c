/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:50:38 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/24 03:55:36 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

//This function verifies that the lines contained by the map are valid.
//That it contains a single player. That it doesnt contain any values aside from
// [0, 1, N, S, W, E, \n]
int	ft_parse3_check_lines(int open_fd, t_data *data)
{
	char	*line;
	int		index;
	bool	flag[2];

	index = 0;
	flag[0] = false;
	flag[1] = false;
	line = 	ft_parse3_util_skip_empty_lines(open_fd);
	if (!line)
		return (ERROR);
	while (line)
	{
		data->map->rows++;
		ft_printf(LOGSV, "[VERBOSE][PARSE3]: Checking map character %c\n", line[index]);
		if (!ft_parse3_util_check_valid_char(line[index], &flag[0], &flag[2]))
			index++;
		else
			return (free(line), get_next_line(open_fd, 1), ft_printf(2, "Error\nFound invalid character\n"), ERROR);
		if (line[index] == '\n')
		{
			ft_printf(LOGSV, "\n");
			line = ft_parse3_util_get_next_map_line(line, open_fd, &index);
		}
	}
	free(line);
	get_next_line(open_fd, 1);
	if (flag[0] == true && flag[1] == false)
		return (close(open_fd), 0);
	if (flag[0] == true)
		ft_printf(2, "Error\nMultiple Players found. Can only be one\n");
	else
		ft_printf(2, "Error\nNo Player found. There has to be one\n");
	return (close(open_fd), ERROR);
}

// ft_parse3_assign_map_to_data(int open_fd, t_data *data)
// {
// 	char	line[MAX_LINE_LEN];
// 	int		len;
	
// 	while (read)
// 	return (0);
// }