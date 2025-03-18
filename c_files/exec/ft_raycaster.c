/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:09:29 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/18 12:03:33 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	ft_raycaster(t_data *data)
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
		ft_init_dda(data->player, data->map, x);
		hit = 0;
		ft_digital_differential_analyzer(data->player, data->map, &hit, &side);
		ft_calculate_line_height(data->player, data, side);
		ft_init_wall_x(data, side);
		data->player->wall_x -= floor(data->player->wall_x);
		ft_draw_vertical(x, data->player, data, &side);
		x++;
	}
}

void	ft_digital_differential_analyzer(t_player *p, t_map *m, int *hit,
	int *side)
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
		if (m->map[m->map_y][m->map_x] == '1')
			*hit = 1;
	}
}

void	ft_calculate_line_height(t_player *p, t_data *data, int side)
{
	if (side == 0)
		data->player->perp_wall_dist = (data->player->side_dist_x - \
			data->player->delta_dist_x);
	else
		data->player->perp_wall_dist = (data->player->side_dist_y - \
			data->player->delta_dist_y);
	if (p->perp_wall_dist < 0.0001)
		p->perp_wall_dist = 0.0001;
	p->line_height = (int)(HEIGHT / p->perp_wall_dist);
	p->draw_start = -p->line_height / 2 + HEIGHT / 2;
	p->draw_end = p->line_height / 2 + HEIGHT / 2;
	if (p->draw_start < 0)
		p->draw_start = 0;
	if (p->draw_end >= HEIGHT)
		p->draw_end = HEIGHT - 1;
}

void	ft_init_wall_x(t_data *data, int side)
{
	if (side == 0)
		data->player->wall_x = data->player->pos_y + \
		data->player->perp_wall_dist * data->player->ray_dir_y;
	else
		data->player->wall_x = data->player->pos_x + \
		data->player->perp_wall_dist * data->player->ray_dir_x;
}
