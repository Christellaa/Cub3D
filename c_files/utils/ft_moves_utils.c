/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:46 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/13 11:53:04 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	move_player_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->dir_x * SPEED;
	new_y = data->player->pos_y + data->player->dir_y * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int	move_player_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->dir_x * SPEED;
	new_y = data->player->pos_y - data->player->dir_y * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int	move_player_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->dir_y * SPEED;
	new_y = data->player->pos_y - data->player->dir_x * SPEED;
	return (is_move_valid(data, new_x, new_y));
}

int	move_player_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->dir_y * SPEED;
	new_y = data->player->pos_y + data->player->dir_x * SPEED;
	return (is_move_valid(data, new_x, new_y));
}
