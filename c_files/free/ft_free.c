/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:09:00 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 03:34:30 by ilevy            ###   ########.fr       */
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

void	ft_clean_exit(t_data *data)
{
	if (data->east_txt)
		free(data->east_txt);
	if (data->north_txt)
		free(data->north_txt);
	if (data->west_txt)
		free(data->west_txt);
	if (data->south_txt)
		free(data->south_txt);
}