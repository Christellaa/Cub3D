/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:47:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/24 06:00:52 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_init_data(t_data *data)
{
	t_rgb 		*ceiling;
	t_rgb 		*floor;
	t_player	*p1;
	t_map		*map;

	ceiling = (t_rgb *)malloc(1 * sizeof(t_rgb));
	floor = (t_rgb *)malloc(1 * sizeof(t_rgb));
	p1 = (t_player *)malloc(1 * sizeof(t_player));
	map = (t_map *)malloc(1 * sizeof(t_map));
	if (!ceiling || !floor || !p1 || !map)
	{
		if (ceiling)
			free(ceiling);
		if (floor)
			free(floor);
		if (p1)
			free(p1);
		if (map)
			free(map);
		return (ft_printf(2, "Error\n Malloc error during init\n"), ERROR);
	}
	ft_init_map(map);
	ft_init_player(p1);
	ft_init_rgbs(ceiling, floor);
	ft_init_data_params(data);
	data->player = p1;
	data->ceiling_rgb = ceiling;
	data->floor_rgb = floor;
	data->map = map;
	return (0);
}

void	ft_init_rgbs(t_rgb *ceiling, t_rgb *floor)
{
	ceiling->assigned = false;
	ceiling->r = 0;
	ceiling->b = 0;
	ceiling->g = 0;
	floor->assigned = false;
	floor->r = 0;
	floor->b = 0;
	floor->g = 0;
}

void	ft_init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
}

void	ft_init_map(t_map *map)
{
	map->map = NULL;
	map->columns = 0;
	map->rows = 0;
}

void	ft_init_data_params(t_data *data)
{
	data->filename = NULL;
	data->north_txt = NULL;
	data->south_txt = NULL;
	data->west_txt = NULL;
	data->east_txt = NULL;
}
