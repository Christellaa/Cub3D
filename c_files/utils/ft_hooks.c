/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:27:14 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/12 15:48:35 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_cross(t_data *data)
{
	ft_clean_exit(data, 0);
	return (0);
}

// int check_player_move(char tile)
// {
// 	if (tile == '1')
// 		return (0);
// 	return (1);
// }

// void move_player(t_data *data, int x, int y)
// {
// 	int new_x;
// 	int new_y;

// 	new_x = data->player->pos_x + x;
// 	new_y = data->player->pos_y + y;
// 	if (!check_player_move(data->minimap->map->map[new_y][new_x]))
// 		return ;
// 	data->map->map[(int)data->player->pos_y][(int)data->player->pos_x] = '2';
// 	data->player->pos_x = new_x;
// 	data->player->pos_y = new_y;
// 	data->map->map[new_y][new_x] = 'N';
// 	render_map2D(data->minimap, data);
// }

// #define LINE_LEN 500  // Length of the line to draw

// int ray_hits_wall(t_minimap *minimap, int y, int x)
// {
// 	if (minimap->map->map[y][x] == '1')
// 		return (1);
// 	return (0);
// }

// void draw_line(t_data *data)
// {
// 	int center_x;
// 	int center_y;
// 	int x;
// 	int y;
// 	int i = 0;

// 	center_x = data->player->pos_x * data->minimap->tile_size + data->minimap->tile_size / 2;
// 	center_y = data->player->pos_y * data->minimap->tile_size + data->minimap->tile_size / 2;
//     while (i < LINE_LEN)
//     {
//         x = center_x + data->player->dir_x * i;
//         y = center_y + data->player->dir_y * i;
// 		if (x >= 0 && x < data->minimap->map->columns * data->minimap->tile_size
// 			&& y >= 0 && y < data->minimap->map->rows * data->minimap->tile_size)
// 		{
// 			if (ray_hits_wall(data->minimap, y/data->minimap->tile_size,
// 				x/data->minimap->tile_size))
// 				break;
// 			int pixel = y * (data->minimap->s_l / 4) + x;
// 			data->minimap->buf[pixel] = 0xff0000;
// 		}
// 		i++;
//     }
// }

// void rotate_angle(t_data *data, int angle)
// {

// 	if (angle < 0)
// 		data->player->camera_x += 2 * PI;
// 	else if (angle > (2 * PI))
// 		data->player->camera_x -= 2 * PI;

// 	data->player->dir_x = cos(data->player->camera_x);
// 	data->player->dir_y = sin(data->player->camera_x);
// 	draw_line(data);
// 	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->img_ptr, 0, 0);
// }

int is_move_in_map(t_map *map, double x, double y)
{
	if (map->map[(int)y][(int)x] != '1')
		return (1);
	return (0);
}

int is_move_valid(t_data *data, double new_x, double new_y)
{
	int move;

	move = 0;
	if (is_move_in_map(data->map, new_x, data->player->pos_y))
	{
		move++;
		data->player->pos_x = new_x;
	}
	if (is_move_in_map(data->map, data->player->pos_x, new_y))
	{
		move++;
		data->player->pos_y = new_y;
	}
	return (move);
}

int move_player_forward(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->pos_x + data->player->dir_x * SPEED;
	new_y = data->player->pos_y + data->player->dir_y * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int move_player_backward(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->pos_x - data->player->dir_x * SPEED;
	new_y = data->player->pos_y - data->player->dir_y * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int move_player_left(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->pos_x + data->player->dir_y * SPEED;
	new_y = data->player->pos_y - data->player->dir_x * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int move_player_right(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player->pos_x - data->player->dir_y * SPEED;
	new_y = data->player->pos_y + data->player->dir_x * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int rotate_player(t_data *data, double rotation)
{
	t_player *p;
	double temp_x;
	double rotation_speed;

	rotation_speed = SPEED * rotation;
	p = data->player;
	temp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotation_speed) - p->dir_y * sin(rotation_speed);
	p->dir_y = temp_x * sin(rotation_speed) + p->dir_y * cos(rotation_speed);
	temp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotation_speed) - p->plane_y * sin(rotation_speed);
	p->plane_y = temp_x * sin(rotation_speed) + p->plane_y * cos(rotation_speed);
	return (1);
}

int move_player(t_data *data)
{
	int move = 0;
	if (data->player->move_y == 1)
	move += move_player_forward(data);
	if (data->player->move_y == -1)
		move += move_player_backward(data);
	if (data->player->move_x == -1)
		move += move_player_left(data);
	if (data->player->move_x == 1)
		move += move_player_right(data);
	if (data->player->rotate != 0)
		move += rotate_player(data, data->player->rotate);
	return (move);
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
	return (0);
}

int ft_key_release_handler(int keycode, t_data *data)
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
	return (0);
}

int render(t_data *data)
{
	if (!move_player(data))
		return (0);
	ft_raycaster(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mlx->img_ptr, 0, 0);
	return (1);
}
