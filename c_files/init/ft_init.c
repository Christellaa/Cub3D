/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:47:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 18:01:33 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_init_data(t_data *data)
{
	t_rgb 		*ceiling;
	t_rgb 		*floor;
	t_player	*p1;

	ceiling = (t_rgb *)malloc(1 * sizeof(t_rgb));
	floor = (t_rgb *)malloc(1 * sizeof(t_rgb));
	p1 = (t_player *)malloc(1 * sizeof(t_player));
	if (!ceiling || !floor || !p1)
	{
		if (ceiling)
			free(ceiling);
		if (floor)
			free(floor);
		if (p1)
			free(p1);
		return (ft_printf(2, "Error\n Malloc error during init\n"), ERROR);
	}
	if (ft_init_rgbs(ceiling, floor) == ERROR || ft_init_player(p1) == ERROR)
		return (ERROR);
	data->player = p1;
	data->ceiling_rgb = ceiling;
	data->floor_rgb = floor;
	data->north_txt = NULL;
	data->south_txt = NULL;
	data->west_txt = NULL;
	data->east_txt = NULL;
	return (0);
}

int	ft_init_rgbs(t_rgb *ceiling, t_rgb *floor)
{
	ceiling->assigned = false;
	ceiling->r = 0;
	ceiling->b = 0;
	ceiling->g = 0;
	floor->assigned = false;
	floor->r = 0;
	floor->b = 0;
	floor->g = 0;
	return (0);
}

int	ft_init_player(t_player *player)
{

	player->pos.x = 0;
	player->pos.y = 0;
	return (0);
}
