/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_try_raycaster.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:09:29 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/03 09:57:17 by ilevy            ###   ########.fr       */
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
		{
			if (data->player->step_x > 0)
				data->player->color = 0xFF0000;
			else
				data->player->color = 0x00FF00;
		}
		else
		{
			if (data->player->step_y > 0)
				data->player->color = 0x0000FF;
			else
				data->player->color = 0xFFFF00;
		}
		ft_draw_vertical(x, data->player, data);
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

void	ft_draw_vertical(int x, t_player *p, t_data *data)
{
	int	y;

	y = p->draw_start;
	while (y < p->draw_end)
	{
		ft_put_pixel(data, x, y, p->color);
		y++;
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
