/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:21:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/17 18:21:57 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

t_pos	get_tile_pos(t_minimap *mmap, double ox, double oy)
{
	t_pos	tile;

	tile.x = (int)(mmap->radius + ox * mmap->tile_size);
	tile.y = (int)(mmap->radius + oy * mmap->tile_size);
	return (tile);
}

void	draw_tile(t_minimap *mmap, t_pos tile, int color)
{
	double		end_x;
	double		end_y;
	double		start_x;
	double		start_y;
	double		dist;

	end_x = tile.x + mmap->tile_size;
	end_y = tile.y + mmap->tile_size;
	start_y = tile.y;
	while (start_y < end_y)
	{
		start_x = tile.x;
		while (start_x < end_x)
		{
			dist = sqrt((start_x - mmap->radius) * (start_x - mmap->radius) \
					+ (tile.y - mmap->radius) * (tile.y - mmap->radius));
			if (dist <= mmap->radius)
				ft_put_pixel_mmap(mmap, (int)start_x, (int)start_y, color);
			start_x++;
		}
		start_y++;
	}
}

void	ft_put_pixel_mmap(t_minimap *mmap, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = mmap->buf + (y * mmap->s_l + x * (mmap->bpp / 8));
	*(unsigned int *)dst = color;
}
