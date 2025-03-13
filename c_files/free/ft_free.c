/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:09:00 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/13 11:48:17 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	ft_free_maps(t_data *data)
{
	if (data->minimap)
	{
		if (data->minimap->img_ptr && data->mlx->mlx)
			mlx_destroy_image(data->mlx->mlx, data->minimap->img_ptr);
		free(data->minimap);
		data->minimap = NULL;
	}
	if (data->map)
	{
		if (data->map->map)
			ft_free_tab(data->map->map);
		free(data->map);
	}
}

void	ft_free_textures(t_data *data)
{
	if (data->east_txt)
	{
		free(data->east_txt->path_to_xpm);
		safe_free_texture(data->east_txt, data->mlx);
		free(data->east_txt);
	}
	if (data->north_txt)
	{
		free(data->north_txt->path_to_xpm);
		safe_free_texture(data->north_txt, data->mlx);
		free(data->north_txt);
	}
	if (data->west_txt)
	{
		free(data->west_txt->path_to_xpm);
		safe_free_texture(data->west_txt, data->mlx);
		free(data->west_txt);
	}
	if (data->south_txt)
	{
		free(data->south_txt->path_to_xpm);
		safe_free_texture(data->south_txt, data->mlx);
		free(data->south_txt);
	}
}

void	ft_clean_exit(t_data *data, int errcode)
{
	if (data->filename)
		free(data->filename);
	ft_free_textures(data);
	if (data->player)
		free(data->player);
	if (data->ceiling_rgb)
		free(data->ceiling_rgb);
	if (data->floor_rgb)
		free(data->floor_rgb);
	ft_free_maps(data);
	if (data->mlx)
		ft_free_mlx(data);
	exit(errcode);
}

void	ft_free_mlx(t_data *data)
{
	if (data->mlx->img_ptr && data->mlx->mlx)
		mlx_destroy_image(data->mlx->mlx, data->mlx->img_ptr);
	if (data->mlx->win && data->mlx->mlx)
		mlx_destroy_window(data->mlx->mlx, data->mlx->win);
	if (data->mlx->name)
		free(data->mlx->name);
	if (data->mlx->mlx)
	{
		mlx_destroy_display(data->mlx->mlx);
		free(data->mlx->mlx);
	}
	free(data->mlx);
	data->mlx = NULL;
}
