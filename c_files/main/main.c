/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:24:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/05 07:37:59 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verify single arg: argc == %d\n", argc);
	if (argc != 2)
	{
		ft_printf(2, USAGE);
		return (ERROR);
	}
	if (ft_init_data(&data) == ERROR)
		ft_clean_exit(&data, ERROR);
	if (ft_parse(argv, &data) == ERROR)
		ft_clean_exit(&data, ERROR);
	ft_printf(2, "Map is:\n");
	while (data.map->map[i])
	{
		ft_printf(2, "%s\n", data.map->map[i]);
		i++;
	}
    double angle = 0;

    if (data.map->direction == 'N') angle = -PI/2;   // -90 degrees (π/2)
    if (data.map->direction == 'S') angle = PI/2;  // 90 degrees (-π/2)
    if (data.map->direction == 'W') angle = PI;     // 180 degrees (π)
	if (data.map->direction == 'E') angle = 0;	// 0 degrees (2π)

    data.player->dir_x = cos(angle);
    data.player->dir_y = sin(angle);


    data.player->plane_x = -sin(angle) * 0.66;
    data.player->plane_y = cos(angle) * 0.66;
	mlx_loop_hook(data.mlx->mlx, ft_raycaster, &data);
	mlx_hook(data.mlx->win, KeyPress, KeyPressMask, ft_key_handler, &data);
	mlx_hook(data.mlx->win, DestroyNotify, StructureNotifyMask,
		ft_cross, &data);
	mlx_loop(data.mlx->mlx);
	ft_clean_exit(&data, 0);
}
