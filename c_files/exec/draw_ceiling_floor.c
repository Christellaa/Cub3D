/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceiling_floor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:38:45 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/13 12:35:03 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	ft_draw_ceiling_floor(t_data *data)
{
	int		x;
	int		y;
	int		c_color;
	int		f_color;
	int		pixel_index;

	y = 0;
	x = 0;
	init_colors(&c_color, &f_color, data);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_index = (y * data->mlx->s_l) + (x * data->mlx->bpp / 8);
			if (y < HEIGHT / 2)
				data->player->color = c_color;
			else
				data->player->color = f_color;
			ft_draw_ceiling_floor2(data, pixel_index);
			x++;
		}
		y++;
	}
}

void	init_colors(int *c_color, int *f_color, t_data *data)
{
	*c_color = (data->ceiling_rgb->r << 16) | (data->ceiling_rgb->g << 8) | \
	data->ceiling_rgb->b;
	*f_color = (data->floor_rgb->r << 16) | (data->floor_rgb->g << 8) | \
	data->floor_rgb->b;
}

void	ft_draw_ceiling_floor2(t_data *data, int pixel_index)
{
	char	*buf;

	buf = data->mlx->buf;
	buf[pixel_index + 0] = data->player->color & 0xFF;
	buf[pixel_index + 1] = (data->player->color >> 8) & 0xFF;
	buf[pixel_index + 2] = (data->player->color >> 16) & 0xFF;
}
