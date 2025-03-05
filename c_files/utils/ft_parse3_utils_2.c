/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:13:05 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/04 20:22:32 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function initializes the lines within each map by strduping them.
int	ft_parse3_util2_initialize_map(char **line, int open_fd, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	if (*line)
	{
		while (*line && ft_util_is_whitespace_only(line) == ERROR
			&& i < data->map->rows)
		{
			len = ft_strlen(*line);
			if (len > data->map->columns)
				data->map->columns = len;
			data->map->map[i] = ft_strdup(*line);
			if (!data->map->map[i])
			{
				ft_printf(2, "Error\nMalloc error in map initialization\n");
				return (get_next_line(open_fd, 1), ERROR);
			}
			if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
				return (get_next_line(open_fd, 1), ERROR);
			i++;
		}
	}
	data->map->map[i] = NULL;
	return (0);
}

// This function verifies that the map contains a single occurence of player.
int	ft_parse3_util2_single_player(t_data *data)
{
	bool	p_flag;
	int		i;
	int		j;
	char	c;

	i = 0;
	p_flag = false;
	while (data->map->map[i])
	{
		j = 0;
		c = data->map->map[i][j];
		while (c != '\0')
		{
			if (ft_p3_isp(c, data->map, j, i) && p_flag == false)
				p_flag = true;
			else if (ft_p3_isp(c, data->map, j, i) && p_flag == true)
				return (ft_printf(2, "Error\nMultiple players.\n"), ERROR);
			j++;
			c = data->map->map[i][j];
		}
		i++;
	}
	if (p_flag == false)
		return (ft_printf(2, "Error\nNo player detected\n"), ERROR);
	return (0);
}

// This function verifies that the char <c> is or isnt a player char.
// If it is, the x and y positions of c are stored and flag is switched to true
int	ft_p3_isp(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (map->p_assigned == false)
		{
			map->direction = c;
			map->map_y = y;
			map->map_x = x;
			map->p_assigned = true;
		}
		return (1);
	}
	return (0);
}

int	ft_parse3_util2_check_map_closed(t_map *map)
{
	t_stack	stack;
	int		*dir_x;
	int		*dir_y;

	stack.top = -1;
	stack.max_size = map->rows * map->columns;
	stack.pos_data = (t_pos *)malloc(sizeof(t_pos) * (stack.max_size));
	if (!stack.pos_data)
		return (ft_printf(2, "Error\nMalloc failure in flood fill\n"), ERROR);
	ft_ff_util_push(&stack, map->map_x, map->map_y);
	dir_x = ft_util_get_dir_x();
	dir_y = ft_util_get_dir_y();
	if (!dir_y || !dir_x)
	{
		free(stack.pos_data);
		if (dir_x)
			free(dir_x);
		return (ft_printf(2, "Error\nMalloc failure in flood fill\n"), ERROR);
	}
	while (!ft_ff_util_is_empty(&stack))
	{
		if (ft_flood_fill_one(&stack, map, dir_x, dir_y) == ERROR)
			return (free(stack.pos_data), free(dir_y), free(dir_x), ERROR);
	}
	return (free(stack.pos_data), free(dir_y), free(dir_x), 0);
}
