/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:24:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/17 18:22:48 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (ft_printf(2, USAGE), ERROR);
	if (ft_init_data(&data) == ERROR)
		ft_clean_exit(&data, ERROR);
	if (ft_parse(argv, &data) == ERROR)
		ft_clean_exit(&data, ERROR);
	mlx_mouse_hide(data.mlx->mlx, data.mlx->win);
	init_player_direction(&data);
	ft_raycaster(&data);
	if (ft_init_minimap(&data) == ERROR)
		ft_clean_exit(&data, ERROR);
	draw_minimap(data.minimap, data.player);
	mlx_put_image_to_window(data.mlx->mlx, data.mlx->win, data.mlx->img_ptr, \
		0, 0);
	hooks(&data);
	mlx_loop(data.mlx->mlx);
	ft_clean_exit(&data, 0);
}

/*
ANGLES:
-PI/2 = -90 degrees = π/2
PI/2 = 90 degrees = -π/2
PI = 180 degrees = π
0 = 0 degrees = 2π
*/
void	init_player_direction(t_data *data)
{
	double	angle;

	if (data->map->direction == 'N')
		angle = -PI / 2;
	if (data->map->direction == 'S')
		angle = PI / 2;
	if (data->map->direction == 'W')
		angle = PI;
	if (data->map->direction == 'E')
		angle = 0;
	data->player->dir_x = cos(angle);
	data->player->dir_y = sin(angle);
	data->player->plane_x = -sin(angle) * 0.66;
	data->player->plane_y = cos(angle) * 0.66;
}

void	hooks(t_data *data)
{
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, ft_key_press_handler, \
		data);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, \
		ft_key_release_handler, data);
	mlx_hook(data->mlx->win, DestroyNotify, StructureNotifyMask, \
		ft_cross, data);
	mlx_hook(data->mlx->win, MotionNotify, PointerMotionMask, mouse_handler, \
		data);
	mlx_loop_hook(data->mlx->mlx, render, data);
}
