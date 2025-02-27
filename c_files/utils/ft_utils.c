/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:13:33 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/27 23:35:59 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks the entire line is comprised of whitespace characters
// returns 0 if true, error otherwise.
int	ft_util_is_whitespace_only(char **line)
{
	int	i;

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
	{
		if ((*line)[ft_strlen(*line) - 1] == '\n')
			(*line)[ft_strlen(*line) - 1] = '\0';
	}
	return (0);
}

int	*ft_util_get_dir_x(void)
{
	int	*dir_x;

	dir_x = NULL;
	dir_x = (int *)malloc(sizeof(int) * 8);
	if (!dir_x)
	{
		ft_printf(2, "lol");
		free(dir_x);
		return (ft_printf(2, "Error\nMalloc fail in flood fill\n"), NULL);
	}
	dir_x[0] = -1;
	dir_x[1] = -1;
	dir_x[2] = -1;
	dir_x[3] = 0;
	dir_x[4] = 1;
	dir_x[5] = 1;
	dir_x[6] = 1;
	dir_x[7] = 0;
	return (dir_x);
}

int	*ft_util_get_dir_y(void)
{
	int	*dir_y;

	dir_y = NULL;
	dir_y = (int *)malloc(sizeof(int) * 8);
	if (!dir_y)
	{
		ft_printf(2, "lol");
		free(dir_y);
		return (ft_printf(2, "Error\nMalloc fail in flood fill\n"), NULL);
	}
	dir_y[0] = -1;
	dir_y[1] = 0;
	dir_y[2] = 1;
	dir_y[3] = 1;
	dir_y[4] = 1;
	dir_y[5] = 0;
	dir_y[6] = -1;
	dir_y[7] = -1;
	return (dir_y);
}
