/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 00:50:29 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/22 02:52:07 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_files/cub3d.h"

int	main(int argc, char **argv)
{
	t_data data;
	t_rgb ceiling;
	t_rgb floor;
	int	*rgb_slots;

	rgb_slots = (int *)malloc(3 * sizeof(int));
	rgb_slots[0] = 0;
	rgb_slots[1] = 0;
	rgb_slots[2] = 0;
	ceiling.assigned = false;
	ceiling.B = 0;
	ceiling.R = 0;
	ceiling.B = 0;
	floor.assigned = false;
	floor.B = 0;
	floor.R = 0;
	floor.B = 0;
	data.north_txt = NULL;
	data.south_txt = NULL;
	data.east_txt = NULL;
	data.west_txt = NULL;
	data.ceiling_rgb = ceiling;
	data.floor_rgb = floor;
	ft_parse(argc, argv, &data);
	free(rgb_slots);
	return (0);	
}