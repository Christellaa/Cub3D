/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:34:12 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/28 00:57:25 by ilevy            ###   ########.fr       */
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
	mlx->buf = (int *)mlx_get_data_addr(mlx->img_ptr,
			&mlx->bpp, &mlx->s_l, &mlx->e);
	return (0);
}
