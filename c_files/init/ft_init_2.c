/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:34:12 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/17 17:48:39 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (ERROR);
	mlx->width = WIDTH;
	mlx->height = HEIGHT;
	mlx->name = ft_strdup("Cube3D");
	if (!mlx->name)
		return (ERROR);
	mlx->win = mlx_new_window(mlx->mlx, mlx->width,
			mlx->height, mlx->name);
	if (!mlx->win)
		return (ERROR);
	mlx->img_ptr = mlx_new_image(mlx->mlx, mlx->width,
			mlx->height);
	if (!mlx->img_ptr)
		return (ERROR);
	mlx->buf = mlx_get_data_addr(mlx->img_ptr,
			&mlx->bpp, &mlx->s_l, &mlx->e);
	return (0);
}

int	ft_init_minimap(t_data *data)
{
	data->minimap->map = data->map;
	data->minimap->radius = 150;
	data->minimap->tile_size = 10;
	data->minimap->buf = (int *)mlx_get_data_addr(data->mlx->img_ptr, \
	&data->minimap->bpp, &data->minimap->s_l, &data->minimap->e);
	return (0);
}

void	ft_init_dda(t_player *p, t_map *m, int x)
{
	p->camera_x = 2 * x / (double) WIDTH - 1;
	p->ray_dir_x = p->dir_x + p->plane_x * p->camera_x;
	p->ray_dir_y = p->dir_y + p->plane_y * p->camera_x;
	m->map_x = (int)p->pos_x;
	m->map_y = (int)p->pos_y;
	if (p->ray_dir_x == 0)
		p->delta_dist_x = 1e30;
	else
		p->delta_dist_x = fabs(1 / p->ray_dir_x);
	if (p->ray_dir_y == 0)
		p->delta_dist_y = 1e30;
	else
		p->delta_dist_y = fabs(1 / p->ray_dir_y);
	ft_init_dda2(p, m);
}

void	ft_init_dda2(t_player *p, t_map *m)
{
	if (p->ray_dir_x < 0)
	{
		p->step_x = -1;
		p->side_dist_x = (p->pos_x - m->map_x) * p->delta_dist_x;
	}
	else
	{
		p->step_x = 1;
		p->side_dist_x = (m->map_x + 1.0 - p->pos_x) * p->delta_dist_x;
	}
	if (p->ray_dir_y < 0)
	{
		p->step_y = -1;
		p->side_dist_y = (p->pos_y - m->map_y) * p->delta_dist_y;
	}
	else
	{
		p->step_y = 1;
		p->side_dist_y = (m->map_y + 1.0 - p->pos_y) * p->delta_dist_y;
	}
}
