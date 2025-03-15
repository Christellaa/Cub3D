/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:46 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/14 12:35:28 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	move_player_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->dir_x * data->player->speed;
	new_y = data->player->pos_y + data->player->dir_y * data->player->speed;
	return (is_move_valid(data, new_x, new_y));
}

int	move_player_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->dir_x * data->player->speed;
	new_y = data->player->pos_y - data->player->dir_y * data->player->speed;
	return (is_move_valid(data, new_x, new_y));
}

int	move_player_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + data->player->dir_y * data->player->speed;
	new_y = data->player->pos_y - data->player->dir_x * data->player->speed;
	return (is_move_valid(data, new_x, new_y));
}

int	move_player_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x - data->player->dir_y * data->player->speed;
	new_y = data->player->pos_y + data->player->dir_x * data->player->speed;
	return (is_move_valid(data, new_x, new_y));
}
