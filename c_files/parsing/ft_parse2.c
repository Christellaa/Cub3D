/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:38:51 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/13 13:34:39 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// Assigns the texture paths to data struct.
int	ft_parse2_assign_texture_to_data(char *path, int num, t_data *data)
{
	if (num == NORTH)
		data->north_txt = init_texture(path, data->mlx);
	else if (num == SOUTH)
		data->south_txt = init_texture(path, data->mlx);
	else if (num == EAST)
		data->east_txt = init_texture(path, data->mlx);
	else if (num == WEST)
		data->west_txt = init_texture(path, data->mlx);
	return (0);
}

t_texture	*init_texture(char *path, t_mlx *mlx)
{
	t_texture	*txt;

	txt = (t_texture *)malloc(sizeof(t_texture));
	if (!txt)
		return (ft_printf(2, "Error\nMalloc failure in parsing\n"), NULL);
	txt->path_to_xpm = ft_strdup(path);
	txt->img = mlx_xpm_file_to_image(mlx->mlx, txt->path_to_xpm, &txt->width, \
		&txt->height);
	if (!txt->img)
		return (ft_printf(2, "Error\nTexture loading failure\n"), NULL);
	txt->addr = mlx_get_data_addr(txt->img, &txt->bpp, &txt->s_l, &txt->e);
	return (txt);
}

//Assigns the RGB values to data struct.
int	ft_parse2_assign_rgb_to_data(t_data *data, int *rgb_values, int num)
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
