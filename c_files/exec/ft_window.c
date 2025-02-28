/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:13:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/28 16:57:28 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void put_pixel(t_data *data, int x, int y, int color)
{
	int i;
	int j;
	int pixel;

	i = 0;
	while (i < data->minimap->tile_size - data->minimap->margin && (y + i)
	< data->mlx->height)
	{
		j = 0;
		while (j < data->minimap->tile_size - data->minimap->margin && (x + j)
		< data->mlx->width)
		{
			pixel = (y + i) * (data->minimap->s_l / 4) + (x + j);
			data->minimap->buf[pixel] = color;
			j++;
		}
		i++;
	}
}

void render_map2D(t_minimap *minimap, t_data *data)
{
	int i;
	int j;
	int x;
	int y;

	i = 0;
	while (i < minimap->map->rows)
	{
		j = 0;
		while (j < minimap->map->columns)
		{
			x = j * minimap->tile_size;
			y = i * minimap->tile_size;
			if (minimap->map->map[i][j] == '1')
				put_pixel(data, x, y, 0x0000FF);
			if (minimap->map->map[i][j] == '2')
				put_pixel(data, x, y, 0xFFFFFF);
			else if (minimap->map->map[i][j] == 'N'
				|| minimap->map->map[i][j] == 'W'
				|| minimap->map->map[i][j] == 'S'
				|| minimap->map->map[i][j] == 'E')
				put_pixel(data, x, y, 0xffffff00);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->img_ptr, 0, 0);
}
