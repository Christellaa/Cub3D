/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_try_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:09:29 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/05 10:49:08 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_raycaster(t_data *data)
{
	int	x;
	int	hit;
	int	side;

	side = 0;
	x = 0;
	if (data->mlx->buf)
		ft_memset(data->mlx->buf, 0, data->mlx->s_l * HEIGHT);
	ft_draw_ceiling_floor(data);
	while (x < WIDTH)
	{
		ft_reinit_2_all(data->player, data->map, x);
		hit = 0;
		ft_digital_differential_analyzer(data->player, data->map, &hit, &side);
		if (side == 0)
			data->player->perp_wall_dist = (data->player->side_dist_x - data->player->delta_dist_x);
		else
			data->player->perp_wall_dist = (data->player->side_dist_y - data->player->delta_dist_y);
		ft_calculate_line_height(data->player);
		if (side == 0)
			data->player->wall_x = data->player->pos_y + data->player->perp_wall_dist * data->player->ray_dir_y;
		else
			data->player->wall_x = data->player->pos_x + data->player->perp_wall_dist * data->player->ray_dir_x;
		data->player->wall_x -= floor(data->player->wall_x);
		ft_draw_vertical(x, data->player, data, &side);
		x++;
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img_ptr, 0, 0);
	return (0);
}
void	ft_fuck_norminette(t_player *p, t_map *m)
{
	if (p->ray_dir_x < 0)
	{
		p->step_x = -1;
		p->side_dist_x = (p->pos_x - m->map_x) * p->delta_dist_x;
	}
	else
	{
		p->step_x = 1;
		p->side_dist_x = (m->map_x + 1 - p->pos_x) * p->delta_dist_x;
	}
	if (p->ray_dir_y < 0)
	{
		p->step_y = -1;
		p->side_dist_y = (p->pos_y - m->map_y) * p->delta_dist_y;
	}
	else
	{
		p->step_y = 1;
		p->side_dist_y = (m->map_y + 1 - p->pos_y) * p->delta_dist_y;
	}
}

void	ft_digital_differential_analyzer(t_player *p, t_map *m, int *hit, int *side)
{

	while (!(*hit))
	{
		if (p->side_dist_x < p->side_dist_y)
		{
			p->side_dist_x += p->delta_dist_x;
			m->map_x += p->step_x;
			*side = 0;
		}
		else
		{
			p->side_dist_y += p->delta_dist_y;
			m->map_y += p->step_y;
			*side = 1;
		}
		if (m->map_y < 0 || m->map_y >= HEIGHT || m->map_x < 0 || m->map_x >= WIDTH)
			*hit = 1;
		if (m->map[m->map_y][m->map_x] == '1')
			*hit = 1;
	}
}

void	ft_draw_ceiling_floor(t_data *data)
{
	int		x;
	int		y;
	int		half;
	int		c_color;
	int		f_color;
	char	*buf;

	half = HEIGHT / 2;
	y = 0;
	x = 0;
	c_color = (data->ceiling_rgb->r << 16) | (data->ceiling_rgb->g << 8) | data->ceiling_rgb->b;
	f_color = (data->floor_rgb->r << 16) | (data->floor_rgb->g << 8) | data->floor_rgb->b;
	buf = data->mlx->buf;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			int	pixel_index = (y * data->mlx->s_l) + (x * data->mlx->bpp / 8);
			if (y < half)
			{
				data->player->color = c_color;
				buf[pixel_index + 0] = data->player->color & 0xFF;
				buf[pixel_index + 1] = (data->player->color >> 8) & 0xFF;
				buf[pixel_index + 2] = (data->player->color >> 16) & 0xFF;
			}
			else
			{
				data->player->color = f_color;
				buf[pixel_index + 0] = data->player->color & 0xFF;
				buf[pixel_index + 1] = (data->player->color >> 8) & 0xFF;
				buf[pixel_index + 2] = (data->player->color >> 16) & 0xFF;
			}
			x++;
		}
		y++;
	}
}

void	ft_calculate_line_height(t_player *p)
{
	if (p->perp_wall_dist < 0.0001)
		p->perp_wall_dist = 0.0001;
	p->line_height = (int) (HEIGHT / p->perp_wall_dist);
	p->draw_start = -p->line_height / 2 + HEIGHT / 2;
	p->draw_end = p->line_height / 2 + HEIGHT / 2;
	if (p->draw_start < 0)
		p->draw_start = 0;
	if (p->draw_end >= HEIGHT)
		p->draw_end = HEIGHT - 1;
}

void	ft_draw_vertical(int x, t_player *p, t_data *data, int *side)
{
	int	y;
	int	txt_y;
	int	txt_x;
	t_texture	*texture;

	y = p->draw_start;
	texture = ft_get_texture(p, data, side);
	txt_x = (int)(p->wall_x * texture->width);
	if ((*side == 0 && p->ray_dir_x > 0) || (*side == 1 && p->ray_dir_y < 0))
		txt_x = texture->width - txt_x - 1;
	while (y < p->draw_end)
	{
		txt_y = ((y - p->draw_start) * texture->height) / (p->draw_end - p->draw_start);
		p->color = ft_get_txt_pixel(texture, txt_x, txt_y);
		ft_put_pixel(data, x, y, p->color);
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

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->mlx->buf + (y * data->mlx->s_l + x * (data->mlx->bpp / 8));
	*(unsigned int *)dst = color;
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
