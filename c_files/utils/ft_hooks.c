/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:27:14 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/05 07:33:28 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_cross(t_data *data)
{
	ft_clean_exit(data, 0);
	return (0);
}

int check_player_move(char tile)
{
	if (tile == '1')
		return (0);
	return (1);
}

void move_player(t_data *data, int x, int y)
{
	int new_x;
	int new_y;

	new_x = data->player->pos_x + x;
	new_y = data->player->pos_y + y;
	if (!check_player_move(data->minimap->map->map[new_y][new_x]))
		return ;
	data->map->map[(int)data->player->pos_y][(int)data->player->pos_x] = '2';
	data->player->pos_x = new_x;
	data->player->pos_y = new_y;
	data->map->map[new_y][new_x] = 'N';
	render_map2D(data->minimap, data);
}

#define LINE_LEN 500  // Length of the line to draw

int ray_hits_wall(t_minimap *minimap, int y, int x)
{
	if (minimap->map->map[y][x] == '1')
		return (1);
	return (0);
}

void draw_line(t_data *data)
{
	int center_x;
	int center_y;
	int x;
	int y;
	int i = 0;

	center_x = data->player->pos_x * data->minimap->tile_size + data->minimap->tile_size / 2;
	center_y = data->player->pos_y * data->minimap->tile_size + data->minimap->tile_size / 2;
    while (i < LINE_LEN)
    {
        x = center_x + data->player->dir_x * i;
        y = center_y + data->player->dir_y * i;
		if (x >= 0 && x < data->minimap->map->columns * data->minimap->tile_size
			&& y >= 0 && y < data->minimap->map->rows * data->minimap->tile_size)
		{
			if (ray_hits_wall(data->minimap, y/data->minimap->tile_size,
				x/data->minimap->tile_size))
				break;
			int pixel = y * (data->minimap->s_l / 4) + x;
			data->minimap->buf[pixel] = 0xff0000;
		}
		i++;
    }
}

void rotate_angle(t_data *data, int angle)
{

	if (angle < 0)
		data->player->camera_x += 2 * PI;
	else if (angle > (2 * PI))
		data->player->camera_x -= 2 * PI;

	data->player->dir_x = cos(data->player->camera_x);
	data->player->dir_y = sin(data->player->camera_x);
	printf("camerax: %f, dirx: %f, diry: %f\n", data->player->camera_x, data->player->dir_x, data->player->dir_y);
	draw_line(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->img_ptr, 0, 0);
}

// !!! need 1 keypress handler and 1 keyrelease handler to rotate and move at the same time
int	ft_key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		ft_clean_exit(data, 0);
	else if (keycode == XK_w)
	{
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + data->player->dir_x * 0.2)] != '1')
			data->player->pos_x += data->player->dir_x * 0.2;
		if (data->map->map[(int)(data->player->pos_y + data->player->dir_y * 0.2)][(int)data->player->pos_x] != '1')
			data->player->pos_y += data->player->dir_y * 0.2;
	}
	else if (keycode == XK_s)
	{
		if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x + data->player->plane_x * 0.2)] != '1')
			data->player->pos_x -= data->player->dir_x * 0.2;
		if (data->map->map[(int)(data->player->pos_y + data->player->plane_y * 0.2)][(int)data->player->pos_x] != '1')
			data->player->pos_y -= data->player->dir_y * 0.2;

	}
	else if (keycode == XK_a)
	{
		if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x - data->player->plane_x * 0.2)] != '1')
			data->player->pos_x -= data->player->plane_x * 0.2;
		if (data->map->map[(int)(data->player->pos_y - data->player->plane_y * 0.2)][(int)data->player->pos_x] != '1')
			data->player->pos_y -= data->player->plane_y * 0.2;
	}
	else if (keycode == XK_d)
	{
		if (data->map->map[(int)(data->player->pos_y)][(int)(data->player->pos_x + data->player->plane_x * 0.2)] != '1')
			data->player->pos_x += data->player->plane_x * 0.2;
		if (data->map->map[(int)(data->player->pos_y + data->player->plane_y * 0.2)][(int)data->player->pos_x] != '1')
			data->player->pos_y += data->player->plane_y * 0.2;
	}
	if (keycode == XK_Right)
	{
		data->player->old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(0.2) - data->player->dir_y * sin(0.2);
		data->player->dir_y = data->player->old_dir_x * sin(0.2) + data->player->dir_y * cos(0.2);
		data->player->old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(0.2) - data->player->plane_y * sin(0.2);
		data->player->plane_y = data->player->old_plane_x * sin(0.2) + data->player->plane_y * cos(0.2);
	}
	else if (keycode == XK_Left)
	{
		data->player->old_dir_x = data->player->dir_x;
		data->player->dir_x = data->player->dir_x * cos(-0.2) - data->player->dir_y * sin(-0.2);
		data->player->dir_y = data->player->old_dir_x * sin(-0.2) + data->player->dir_y * cos(-0.2);
		data->player->old_plane_x = data->player->plane_x;
		data->player->plane_x = data->player->plane_x * cos(-0.2) - data->player->plane_y * sin(-0.2);
		data->player->plane_y = data->player->old_plane_x * sin(-0.2) + data->player->plane_y * cos(-0.2);
	}
	ft_raycaster(data);
	return (0);
}
