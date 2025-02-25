/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:38:51 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 01:39:33 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// Assigns the texture paths to data struct.
int	ft_parse2_assign_texture_to_data(char *path, int num, t_data *data)
{
	if (num == NORTH)
	{
		data->north_txt = ft_strdup(path);
		ft_printf(LOGS, "[PARSE2]: Assigned %s to data->north_txt\n", data->north_txt);
	}
	else if (num == SOUTH)
	{
		data->south_txt = strdup(path);
		ft_printf(LOGS, "[PARSE2]: Assigned %s to data->south_txt\n", data->south_txt);
	}
	else if (num == EAST)
	{
		data->east_txt = strdup(path);
		ft_printf(LOGS, "[PARSE2]: Assigned %s to data->east_txt\n", data->east_txt);
	}
	else if (num == WEST)
	{
		data->west_txt = strdup(path);
		ft_printf(LOGS, "[PARSE2]: Assigned %s to data->west_txt\n", data->west_txt);
	}
	return (0);
}

//Assigns the RGB values to data struct.
int	ft_parse2_assign_RGB_to_data(t_data *data, int *rgb_values, int num)
{
	if (num == CEILING)
	{
		ft_printf(LOGS, "[PARSE2]: Assigned RGB values to data->ceiling\n");
		data->ceiling_rgb->assigned = true;
		data->ceiling_rgb->r = rgb_values[0];
		data->ceiling_rgb->g = rgb_values[1];
		data->ceiling_rgb->b = rgb_values[2];
	}
	else
	{
		ft_printf(LOGS, "[PARSE2]: Assigned RGB values to data->floor\n");
		data->floor_rgb->assigned = true;
		data->floor_rgb->r = rgb_values[0];
		data->floor_rgb->g = rgb_values[1];
		data->floor_rgb->b = rgb_values[2];
	}
	return (0);
}

