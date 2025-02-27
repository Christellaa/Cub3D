/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 01:46:34 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/27 05:26:39 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

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

t_pos	ft_ff_util_pop(t_stack *stack)
{
	t_pos	popped;

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

bool	ft_ff_util_is_empty(t_stack *stack)
{
	if (stack->top == -1)
		return (true);
	return (false);
}

void	ft_ff_util_push_8_way(t_stack *stack, int x, int y)
{
	ft_ff_util_push(stack, x - 1, y);
	ft_ff_util_push(stack, x + 1, y);
	ft_ff_util_push(stack, x, y - 1);
	ft_ff_util_push(stack, x, y + 1);
	ft_ff_util_push(stack, x - 1, y - 1);
	ft_ff_util_push(stack, x + 1, y - 1);
	ft_ff_util_push(stack, x - 1, y + 1);
	ft_ff_util_push(stack, x + 1, y + 1);
}
