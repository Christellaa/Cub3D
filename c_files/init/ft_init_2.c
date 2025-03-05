/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:34:12 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/05 07:16:00 by ilevy            ###   ########.fr       */
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

int ft_init_minimap(t_data *data)
{
	data->minimap->map = data->map;
	data->minimap->img_ptr = mlx_new_image(data->mlx->mlx, data->mlx->width,
		data->mlx->height);
	if (!data->minimap->img_ptr)
		return (ERROR);
	data->minimap->buf = (int *)mlx_get_data_addr(data->minimap->img_ptr,
	&data->minimap->bpp, &data->minimap->s_l, &data->minimap->e);
	data->minimap->tile_size = 32;
	data->minimap->margin = 1;
	return (0);
}

void	ft_reinit_2_all(t_player *p, t_map *m, int x)
{
	p->camera_x = 2 * x / (double) WIDTH - 1;
	p->ray_dir_x = p->dir_x + p->plane_x * p->camera_x;
	p->ray_dir_y = p->dir_y + p->plane_y * p->camera_x;
	m->map_x = (int)p->pos_x;
	m->map_y = (int)p->pos_y;
	p->delta_dist_x = (p->ray_dir_x == 0) ? 1e30 : fabs(1 / p->ray_dir_x);
	p->delta_dist_y = (p->ray_dir_y == 0) ? 1e30 : fabs(1 / p->ray_dir_y);
	ft_fuck_norminette(p, m);
}
