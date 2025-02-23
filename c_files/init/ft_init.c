/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:47:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 03:28:38 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	ft_init_data(t_data *data)
{
	t_rgb ceiling;
	t_rgb floor;
	
	ft_init_rgbs(&ceiling, &floor);
	data->ceiling_rgb = &ceiling;
	data->floor_rgb = &floor;
	data->north_txt = NULL;
	data->south_txt = NULL;
	data->west_txt = NULL;
	data->east_txt = NULL;
}

void	ft_init_rgbs(t_rgb *ceiling, t_rgb *floor)
{
	ceiling->assigned = false;
	ceiling->R = 0;
	ceiling->B = 0;
	ceiling->G = 0;
	floor->assigned = false;
	floor->R = 0;
	floor->B = 0;
	floor->G = 0;
}