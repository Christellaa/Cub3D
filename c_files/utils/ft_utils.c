/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:13:33 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 07:12:20 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks the entire line is comprised of whitespace characters
// returns 0 if true, error otherwise.
int	ft_util_is_whitespace_only(char **line)
{
	int i;

	i = 0;
 	while ((*line)[i])
	{
		if (!ft_iswhitespace((*line)[i]) && (*line)[i] != '\n')
			return (ERROR);
		i++;
	}
	return (0);
}

// This function does a GNL that verifies it didnt encounter a malloc error.
int	ft_util_safe_gnl(char **line, int fd, int mode)
{
	if ((*line))
		free((*line));
	(*line) = NULL;
	(*line) = get_next_line(fd, mode);
	if (!(*line))
	{
		if (errno == ENOMEM)
		{
			ft_printf(2, "Error\nMalloc failure in GNL\n");
			return (ERROR);
		}
		ft_printf(LOGSV, "[VERBOSE][UTIL]: Safe GNL: EOF Reached!\n");
		return (1);
	}
	if (*line)
		(*line)[ft_strlen(*line) - 1] = '\0';
	return (0);
}
