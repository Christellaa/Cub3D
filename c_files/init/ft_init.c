/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:47:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/27 02:14:38 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_init_data(t_data *data)
{
	ft_init_data_params(data);
	data->ceiling_rgb = (t_rgb *)malloc(1 * sizeof(t_rgb));
	data->floor_rgb = (t_rgb *)malloc(1 * sizeof(t_rgb));
	data->player = (t_player *)malloc(1 * sizeof(t_player));
	data->map = (t_map *)malloc(1 * sizeof(t_map));
	if (!data->ceiling_rgb || !data->floor_rgb || !data->player || !data->map)
	{
		if (data->map)
			data->map->map = NULL;
		return (ft_printf(2, "Error\n Malloc error during init\n"), ERROR);
	}
	ft_init_map(data->map);
	ft_init_player(data->player);
	ft_init_rgbs(data->ceiling_rgb, data->floor_rgb);
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
	map->p_assigned = false;
	map->p_pos_x = -42;
	map->p_pos_y = -42;
}

void	ft_init_data_params(t_data *data)
{
	data->filename = NULL;
	data->north_txt = NULL;
	data->south_txt = NULL;
	data->west_txt = NULL;
	data->east_txt = NULL;
}
