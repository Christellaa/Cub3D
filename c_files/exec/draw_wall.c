/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:34 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/13 14:05:38 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	ft_draw_vertical(int x, t_player *p, t_data *data, int *side)
{
	int			y;
	int			txt_x;
	t_texture	*texture;
	double		step;
	double		txt_pos;

	y = p->draw_start;
	texture = ft_get_texture(p, data, side);
	txt_x = (int)(p->wall_x * texture->width) % texture->width;
	if ((*side == 0 && p->ray_dir_x > 0) || (*side == 1 && p->ray_dir_y < 0))
		txt_x = (texture->width + (texture->width - txt_x - 1)) % \
		texture->width;
	step = 1.0 * texture->height / p->line_height;
	txt_pos = (p->draw_start - HEIGHT / 2 + p->line_height / 2) * step;
	while (y < p->draw_end)
	{
		ft_draw_vertical2(data->player, txt_pos, texture, txt_x);
		ft_put_pixel(data, x, y, p->color);
		txt_pos += step;
		y++;
	}
}

t_texture	*ft_get_texture(t_player *p, t_data *data, int *side)
{
	if (*side == 0)
	{
		if (p->ray_dir_x > 0)
			return (data->east_txt);
		else
			return (data->west_txt);
	}
	else
	{
		if (p->ray_dir_y > 0)
			return (data->south_txt);
		else
			return (data->north_txt);
	}
}

void	ft_draw_vertical2(t_player *p, double txt_pos, t_texture *texture,
	int txt_x)
{
	int	txt_y;

	txt_y = (texture->height + (int)txt_pos) % texture->height;
	p->color = ft_get_txt_pixel(texture, txt_x, txt_y);
}

int	ft_get_txt_pixel(t_texture *txt, int x, int y)
{
	char	*pixel;
	int		color;

	if (x < 0 || x >= txt->width || y < 0 || y >= txt->height)
		return (0);
	pixel = txt->addr + (y * txt->s_l + x * (txt->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->mlx->buf + (y * data->mlx->s_l + x * (data->mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
