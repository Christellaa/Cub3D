/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:13:33 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/24 03:36:26 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_util_malloc_or_eof(char *buffer, int *bytes_read, int open_fd)
{
	*bytes_read = read(open_fd, buffer, 1);
	if (*bytes_read == 0)
		return (0);
	else if (*bytes_read == -1)
	{
		ft_printf(2, "Error\nCouldn't read from file\n");
		return (-1);
	}
	return (ERROR);
}