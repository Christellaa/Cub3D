/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:47:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/15 09:46:50 by cde-sous         ###   ########.fr       */
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
	data->mlx = (t_mlx *)malloc(1 * sizeof(t_mlx));
	data->minimap = (t_minimap *)malloc(1 * sizeof(t_minimap));
	if (!data->ceiling_rgb || !data->floor_rgb || !data->player || !data->map
		|| !data->mlx)
	{
		if (data->map)
			data->map->map = NULL;
		return (ft_printf(2, "Error\nMalloc error during init\n"), ERROR);
	}
	if (ft_init_mlx(data->mlx) == ERROR)
		return (ft_printf(2, "Error\nMalloc error during mlx init\n"), ERROR);
	if (ft_init_minimap(data) == ERROR)
		return (ft_printf(2, "Error\nMalloc error during minimap init\n"),
			ERROR);
	ft_init_map(data->map);
	ft_init_player(data->player);
	ft_init_rgbs(data->ceiling_rgb, data->floor_rgb);
	return (0);
}

void	ft_init_data_params(t_data *data)
{
	data->filename = NULL;
	data->north_txt = NULL;
	data->south_txt = NULL;
	data->west_txt = NULL;
	data->east_txt = NULL;
	data->time = 0;
	data->old_time = 0;
}

void	ft_init_map(t_map *map)
{
	map->map = NULL;
	map->columns = 0;
	map->rows = 0;
	map->p_assigned = false;
	map->map_x = -42;
	map->map_y = -42;
}

void	ft_init_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->camera_x = 0;
	player->ray_dir_x = 0;
	player->ray_dir_y = 0;
	player->move_x = 0;
	player->move_y = 0;
	player->prev_mouse_x = 0;
	player->rotate = 0;
	player->speed = SPEED;
	ft_printf(2, "SPEEEEEED IS %d\n", player->speed);
	player->mouse_speed = MOUSE_SPEED;
	player->key_speed = SPEED;
	player->ctrl_pressed = false;
	player->shift_pressed = false;
	player->has_moved = false;
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
