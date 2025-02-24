/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:13:33 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/24 06:55:42 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_util_malloc_or_eof(int open_fd)
{
	char	buffer[1];
	int		bytes_read;
	
	bytes_read = read(open_fd, buffer, 1);
	if (bytes_read == 0)
		return (0);
	else if (bytes_read == -1)
	{
		ft_printf(2, "Error\nCouldn't read from file\n");
		return (-1);
	}
	return (ERROR);
}

int	ft_util_check_whitespace_only(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_iswhitespace(line[i]) && line[i] != '\n')
			return (ERROR);
		i++;
	}
	return (0);
}