/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:38:51 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/12 16:18:21 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// Assigns the texture paths to data struct.
int	ft_parse2_assign_texture_to_data(char *path, int num, t_data *data)
{
	if (num == NORTH)
	{
		data->north_txt = (t_texture *)malloc(sizeof(t_texture));
		if (!data->north_txt)
			return (ft_printf(2, "Error\nMalloc failure in parsing\n"), ERROR);
		data->north_txt->path_to_xpm = ft_strdup(path);
		data->north_txt->img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->north_txt->path_to_xpm, &data->north_txt->width,
			&data->north_txt->height);
		if (!data->north_txt->img)
			return(ft_printf(2, "Error\nTexture loading failure\n"), ERROR);
		data->north_txt->addr = mlx_get_data_addr(data->north_txt->img,
			&data->north_txt->bpp, &data->north_txt->s_l, &data->north_txt->e);
	}
	else if (num == SOUTH)
	{
		data->south_txt = (t_texture *)malloc(sizeof(t_texture));
		if (!data->south_txt)
			return (ft_printf(2, "Error\nMalloc failure in parsing\n"), ERROR);
		data->south_txt->path_to_xpm = strdup(path);
		data->south_txt->img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->south_txt->path_to_xpm, &data->south_txt->width,
			&data->south_txt->height);
		if (!data->south_txt->img)
			return(ft_printf(2, "Error\nTexture loading failure\n"), ERROR);
		data->south_txt->addr = mlx_get_data_addr(data->south_txt->img,
			&data->south_txt->bpp, &data->south_txt->s_l, &data->south_txt->e);
	}
	else if (num == EAST)
	{
		data->east_txt = (t_texture *)malloc(sizeof(t_texture));
		if (!data->east_txt)
			return (ft_printf(2, "Error\nMalloc failure in parsing\n"), ERROR);
		data->east_txt->path_to_xpm = strdup(path);
		data->east_txt->img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->east_txt->path_to_xpm, &data->east_txt->width,
			&data->east_txt->height);
		if (!data->east_txt->img)
			return(ft_printf(2, "Error\nTexture loading failure\n"), ERROR);
		data->east_txt->addr = mlx_get_data_addr(data->east_txt->img,
			&data->east_txt->bpp, &data->east_txt->s_l, &data->east_txt->e);
	}
	else if (num == WEST)
	{
		data->west_txt = (t_texture *)malloc(sizeof(t_texture));
		if (!data->west_txt)
			return (ft_printf(2, "Error\nMalloc failure in parsing\n"), ERROR);
		data->west_txt->path_to_xpm = strdup(path);
		data->west_txt->img = mlx_xpm_file_to_image(data->mlx->mlx,
			data->west_txt->path_to_xpm, &data->west_txt->width,
			&data->west_txt->height);
		if (!data->west_txt->img)
			return(ft_printf(2, "Error\nTexture loading failure\n"), ERROR);
		data->west_txt->addr = mlx_get_data_addr(data->west_txt->img,
			&data->west_txt->bpp, &data->west_txt->s_l, &data->west_txt->e);
	}
	return (0);
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
