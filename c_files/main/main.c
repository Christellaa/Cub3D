/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:24:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/21 01:16:43 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int main(int argc, char **argv)
{
	t_data data;

	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying single argument: argc == %d\n", argc);
	if (argc != 2)
	{
		ft_printf(2, "Error\nWrong args number.\nUsage: cub3d [map_file.cub]\n");
		return (ERROR);
	}
	ft_init(&data);
	if (ft_parse(argc, argv, &data) == ERROR)
		return (clean_exit(ERROR));
}

