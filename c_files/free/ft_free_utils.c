/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:41:16 by cde-sous          #+#    #+#             */
/*   Updated: 2025/03/13 11:48:13 by cde-sous         ###   ########.fr       */
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

void	safe_free_texture(t_texture *txt, t_mlx *mlx)
{
	if (txt->img)
		mlx_destroy_image(mlx->mlx, txt->img);
}
