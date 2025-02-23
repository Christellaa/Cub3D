/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:24:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 17:53:06 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verify single arg: argc == %d\n", argc);
	if (argc != 2)
	{
		ft_printf(2, "Error\nWrong args number.\nUsage: cub3d [map_file.cub]\n");
		return (ERROR);
	}
	if (ft_init_data(&data) == ERROR)
		return (ERROR);
	if (ft_parse(argv, &data) == ERROR)
		return (ERROR);
	ft_printf(2, "No errors found!\n");
	ft_clean_exit(&data);
	return (0);
}
