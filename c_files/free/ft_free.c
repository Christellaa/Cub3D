/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:09:00 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/28 01:56:01 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

void	ft_free_tab(char **split)
{
	int	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_clean_exit(t_data *data, int errcode)
{
	if (data->mlx)
		ft_free_mlx(data);
	if (data->filename)
		free(data->filename);
	if (data->east_txt)
		free(data->east_txt);
	if (data->north_txt)
		free(data->north_txt);
	if (data->west_txt)
		free(data->west_txt);
	if (data->south_txt)
		free(data->south_txt);
	if (data->player)
		free(data->player);
	if (data->ceiling_rgb)
		free(data->ceiling_rgb);
	if (data->floor_rgb)
		free(data->floor_rgb);
	if (data->map)
	{
		if (data->map->map)
			ft_free_tab(data->map->map);
		free(data->map);
	}
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
