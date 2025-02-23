/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:50:38 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 17:40:51 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

//This function verifies that the lines contained by the map are valid.
int	ft_parse3_check_lines(int open_fd)
{
	char	*line;
	int		index;
	bool	flag[2];

	index = 0;
	flag[0] = false;
	flag[1] = false;
	line = NULL;
	line = ft_parse3_util_get_next_map_line(line, open_fd);
	while (line[index])
	{
		if (!ft_parse3_util_check_valid_char(line[index], &flag[0], &flag[2]))
			index++;
		else
			return (ft_printf(2, "Error\nFound invalid character\n")ERROR);
		if (line[index] == '\0')
			line = ft_parse3_util_get_next_map_line(line, open_fd);
	}
	free(line);
	get_next_line(open_fd, 1);
	if (flag[0] == true && flag[1] == false)
		return (0);
	ft_printf(2, "Error\nMultiple Players found. Can only be one\n");
	return (ERROR);
}
