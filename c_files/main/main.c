/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:24:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/28 15:35:46 by cde-sous         ###   ########.fr       */
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
	printf("The player is at %f %f\n", data.player->pos_x, data.player->pos_y);
	render_map2D(data.minimap, &data);
	mlx_hook(data.mlx->win, KeyPress, KeyPressMask, ft_key_handler, &data);
	mlx_hook(data.mlx->win, DestroyNotify, StructureNotifyMask,
		ft_cross, &data);
	mlx_loop(data.mlx->mlx);
	ft_clean_exit(&data, 0);
}
