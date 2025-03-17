/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:27:14 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/17 18:22:54 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_cross(t_data *data)
{
	ft_clean_exit(data, 0);
	return (0);
}

int	ft_key_press_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_clean_exit(data, 0);
	if (keycode == XK_w)
		data->player->move_y = 1;
	if (keycode == XK_s)
		data->player->move_y = -1;
	if (keycode == XK_a)
		data->player->move_x = -1;
	if (keycode == XK_d)
		data->player->move_x = 1;
	if (keycode == XK_Left)
		data->player->rotate -= 1;
	if (keycode == XK_Right)
		data->player->rotate += 1;
	if (keycode == XK_Control_L)
	{
		data->player->ctrl_pressed = true;
		mlx_mouse_show(data->mlx->mlx, data->mlx->win);
	}
	if (keycode == XK_Shift_L)
	{
		data->player->shift_pressed = true;
		data->player->speed *= 1.5;
	}
	return (0);
}

int	ft_key_release_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_clean_exit(data, 0);
	if (keycode == XK_w && data->player->move_y == 1)
		data->player->move_y = 0;
	if (keycode == XK_s && data->player->move_y == -1)
		data->player->move_y = 0;
	if (keycode == XK_a && data->player->move_x == -1)
		data->player->move_x = 0;
	if (keycode == XK_d && data->player->move_x == 1)
		data->player->move_x = 0;
	if (keycode == XK_Left && data->player->rotate <= 1)
		data->player->rotate = 0;
	if (keycode == XK_Right && data->player->rotate >= -1)
		data->player->rotate = 0;
	if (keycode == XK_Control_L && data->player->ctrl_pressed == true)
	{
		data->player->ctrl_pressed = false;
		mlx_mouse_hide(data->mlx->mlx, data->mlx->win);
	}
	if (keycode == XK_Shift_L && data->player->shift_pressed == true)
	{
		data->player->shift_pressed = false;
		data->player->speed /= 1.5;
	}
	return (0);
}

int	mouse_handler(int x, int y, t_data *data)
{
	(void)y;
	if (x == data->player->prev_mouse_x)
		return (0);
	if (data->player->ctrl_pressed == false)
	{
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, WIDTH / 2, HEIGHT / 2);
		if (x < data->player->prev_mouse_x)
			rotate_player(data, -1);
		else if (x > data->player->prev_mouse_x)
			rotate_player(data, 1);
		data->player->has_moved = true;
		data->player->prev_mouse_x = x;
	}
	return (0);
}

int	render(t_data *data)
{
	if (!move_player(data))
		return (0);
	data->player->has_moved = false;
	ft_raycaster(data);
	draw_minimap(data->minimap, data->player);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, \
		data->mlx->img_ptr, 0, 0);
	return (1);
}
