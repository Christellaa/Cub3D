/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:46:34 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/13 13:33:45 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks if the stack is empty
bool	ft_ff_util_is_empty(t_stack *stack)
{
	if (stack->top == -1)
		return (true);
	return (false);
}

int	ft_flood_fill_one(t_stack *stack, t_map *map, int *dir_x, int *dir_y)
{
	t_pos		c;
	int			i;
	int			new_y;
	int			new_x;

	c = ft_ff_util_pop(stack, &i);
	if ((map->map[c.y][c.x] == ' ' || map->map[c.y][c.x - 1] == '\n'))
		return (ft_printf(2, "Error\nInvalid map\n"), ERROR);
	if (map->map[c.y][c.x] != '0' && !ft_p3_isp(map->map[c.y][c.x], map, 0, 0))
		return (0);
	if (map->map[c.y][c.x] == '0')
		map->map[c.y][c.x] = '2';
	while (i < 8)
	{
		new_x = c.x + dir_x[i];
		new_y = c.y + dir_y[i++];
		if (ft_flood_fill_check_char(new_y, new_x, map) == ERROR)
			return (ERROR);
		if (map->map[new_y] && map->map[new_y][new_x] == '0')
			ft_ff_util_push(stack, new_x, new_y);
	}
	return (0);
}

//This function pops the current position to the top of the stack
t_pos	ft_ff_util_pop(t_stack *stack, int *i)
{
	t_pos	popped;

	*i = 0;
	if (stack->top == -1)
	{
		popped.x = 0;
		popped.y = 0;
	}
	else
	{
		popped = stack->pos_data[stack->top];
		stack->top--;
	}
	return (popped);
}

int	ft_flood_fill_check_char(int new_y, int new_x, t_map *map)
{
	if (new_y < 0 || new_y >= map->rows || new_x < 0
		|| new_x >= (int)ft_strlen(map->map[new_y]))
		return (ft_printf(2, "Error\nInvalid map: Reach border\n"), ERROR);
	if (!map->map[new_y] || (map->map[new_y][new_x] == ' '
		|| map->map[new_y][new_x] == '\n'))
		return (ft_printf(2, "Error\nInvalid map: Invalid char\n"), ERROR);
	return (0);
}

// This function pushes the current position to the top of the stack
void	ft_ff_util_push(t_stack *stack, int x, int y)
{
	t_pos	pos;

	if (stack->top < stack->max_size - 1)
	{
		pos.x = x;
		pos.y = y;
		stack->top++;
		stack->pos_data[stack->top] = pos;
	}
}
