/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:51:05 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/13 17:31:16 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	move_player(t_data *data)
{
	if (data->player->move_y == 1)
		data->player->has_moved += move_player_forward(data);
	if (data->player->move_y == -1)
		data->player->has_moved += move_player_backward(data);
	if (data->player->move_x == -1)
		data->player->has_moved += move_player_left(data);
	if (data->player->move_x == 1)
		data->player->has_moved += move_player_right(data);
	if (data->player->rotate != 0)
		data->player->has_moved += rotate_player(data, data->player->rotate);
	return (data->player->has_moved);
}

int	rotate_player(t_data *data, double rotation)
{
	t_player	*p;
	double		temp_x;
	double		rotation_speed;

	rotation_speed = SPEED * rotation;
	p = data->player;
	temp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotation_speed) - p->dir_y * sin(rotation_speed);
	p->dir_y = temp_x * sin(rotation_speed) + p->dir_y * cos(rotation_speed);
	temp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotation_speed) - p->plane_y * \
		sin(rotation_speed);
	p->plane_y = temp_x * sin(rotation_speed) + p->plane_y * \
		cos(rotation_speed);
	return (1);
}

int	is_move_valid(t_data *data, double new_x, double new_y)
{
	int	move;

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

int	is_move_in_map(t_map *map, double x, double y)
{
	if (map->map[(int)y][(int)x] != '1')
		return (1);
	return (0);
}
