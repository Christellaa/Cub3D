/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 06:13:05 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/27 05:27:04 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

int	ft_parse3_util2_initialize_map(char **line, int open_fd, t_data *data)
{
	int	i;
	int	len;

	i = 0;
	if (*line)
	{
		while (*line && ft_util_is_whitespace_only(line) == ERROR && i < data->map->rows)
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
			ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL2]: assigned %s\n", data->map->map[i]);
			i++;
		}
	}
	data->map->map[i] = NULL;
	ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL2]: assigned %s\n", data->map->map[i]);
	return (0);
}

int	ft_parse3_util2_single_player(t_data *data)
{
	bool	p_flag;
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	p_flag = false;
	while (data->map->map[i])
	{
		c = data->map->map[i][j];
		while (c != '\0')
		{
			if (ft_parse3_util2_is_player(c, data->map, j, i) && p_flag == false)
				p_flag = true;
			else if (ft_parse3_util2_is_player(c, data->map, j, i) && p_flag == true)
			{
				ft_printf(2, "Error\nMultiple players detected.\n");
				return (ERROR);
			}
			j++;
			c = data->map->map[i][j];
		}
		j = 0;
		i++;
	}
	if (p_flag == false)
	{
		ft_printf(2, "Error\nNo player detected\n");
		return (ERROR);
	}
	ft_printf(LOGSV, "[VERBOSE][PARSE3_UTIL2]: Only one player found\n");
	return (0);
}

int	ft_parse3_util2_is_player(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
	{
		if (map->p_assigned == false)
		{
			map->p_pos_y = y;
			map->p_pos_x = x;
			map->p_assigned = true;
		}
		return (1);
	}
	return (0);
}
int	ft_parse3_util2_check_map_closed(t_map *map)
{
	t_stack	stack;
	static int dir_x[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
	static int dir_y[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
	
	stack.top = -1;
	stack.max_size = map->rows * map->columns;
	stack.pos_data = (t_pos *)malloc(sizeof(t_pos) * (stack.max_size));
	if (!stack.pos_data)
	{
		ft_printf(2, "Error\nMalloc failure in flood fill\n");
		return (ERROR);
	}
	ft_ff_util_push(&stack, map->p_pos_x, map->p_pos_y);
	while (!ft_ff_util_is_empty(&stack))
	{
		t_pos	curr;
		curr = ft_ff_util_pop(&stack);
		if ((map->map[curr.y][curr.x] == ' ' || map->map[curr.y][curr.x - 1] == '\n'))
		{
			ft_printf(2, "Error\nInvalid map\n");
			free(stack.pos_data);
			return (ERROR);
		}
		if (map->map[curr.y][curr.x] != '0' && !ft_parse3_util2_is_player(map->map[curr.y][curr.x], map, 0, 0))	
			continue ;
		map->map[curr.y][curr.x] = '2';
		for (int i = 0; i < 8; i++)
		{
			int new_x = curr.x + dir_x[i];
			int new_y = curr.y + dir_y[i];
			if (new_y < 0 || new_y >= (int)ft_strlen(map->map[new_y])|| new_x < 0 || new_x >= (int)ft_strlen(map->map[new_y]))
			{
				ft_printf(2, "Error\nInvalid map: Reached border\n");
				free(stack.pos_data);
				return (ERROR);
			}
			if (!map->map[new_y] || (map->map[new_y][new_x] == ' ' || map->map[new_y][new_x] == '\n'))
			{
				ft_printf(2, "Error\nInvalid map: Found unrenderable character\n");
				free(stack.pos_data);
				return (ERROR);
			}
			if (map->map[new_y] && map->map[new_y][new_x] == '0')
				ft_ff_util_push(&stack, new_x, new_y);
		}
	}
	free(stack.pos_data);
	return (0);
}
