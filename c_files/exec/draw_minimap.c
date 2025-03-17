/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 10:05:50 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/17 18:21:53 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	draw_minimap(t_minimap *mmap, t_player *p)
{
	double	range;
	double	offset_x;
	double	offset_y;

	draw_circle_outline(mmap, 0x000000);
	range = (double)mmap->radius / mmap->tile_size;
	offset_y = -range;
	while (offset_y <= range)
	{
		offset_x = -range;
		while (offset_x <= range)
		{
			draw_minimap_tile(mmap, p, offset_x, offset_y);
			offset_x++;
		}
		offset_y++;
	}
	draw_player(mmap, 0x00FF00);
}

void	draw_circle_outline(t_minimap *mmap, int color)
{
	double	tolerance;
	int		x;
	int		y;
	double	dist;

	tolerance = 0.5;
	y = mmap->radius - mmap->radius;
	while (y <= mmap->radius + mmap->radius)
	{
		x = mmap->radius - mmap->radius;
		while (x <= mmap->radius + mmap->radius)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			{
				dist = sqrt((x - mmap->radius) * (x - mmap->radius) \
				+ (y - mmap->radius) * (y - mmap->radius));
				if (fabs(dist - mmap->radius) <= tolerance)
					ft_put_pixel_mmap(mmap, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap_tile(t_minimap *mmap, t_player *p, double ox, double oy)
{
	t_pos	tile;
	int		map_x;
	int		map_y;
	char	c;

	tile = get_tile_pos(mmap, ox, oy);
	map_x = (int)floor(p->pos_x + ox);
	map_y = (int)floor(p->pos_y + oy);
	if (map_y < 0 || map_y >= mmap->map->rows)
		return ;
	if (map_x < 0 || map_x >= (int)ft_strlen(mmap->map->map[map_y]))
		return ;
	c = mmap->map->map[map_y][map_x];
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		c = '2';
	else if (c == '1')
		draw_tile(mmap, tile, 0xFFFFFF);
}

void	draw_player(t_minimap *mmap, int color)
{
	t_pos	tile;

	tile.x = mmap->radius;
	tile.y = mmap->radius;
	draw_tile(mmap, tile, color);
}
