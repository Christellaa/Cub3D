/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse3_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 03:52:26 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 04:26:24 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks that the character <c> being processed is "valid"
// It also verifies that a player exists and that it is singular.
// Another check will be done to verify that spaces aren't in the map, later.
int	ft_parse3_util_check_valid_char(char c, bool *p1_flag, bool *multiple_flag)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (*p1_flag == false)
			(*p1_flag) = true;
		else if (*p1_flag == true)
			(*multiple_flag) = true;
		return (0);
	}
	else if (c == '1' || c == '0' || c == ' ')
		return (0);
	return (ERROR);
}