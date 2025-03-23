/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse1_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 02:59:28 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/23 20:27:44 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

//This function checks that the RGB code follows this strict structure:
// [0, 255],[0, 255],[0,255]
// Broken into 2 for norm reasons.
int	ft_parse1_util_check_valid_rgb(char *line, int *rgb_slots)
{
	int	comma_counter;
	int	i;

	i = 0;
	comma_counter = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma_counter++;
		else if (line[i] == ' ')
		{
			ft_printf(2, "Error\nRGB format strictly prohibits whitespaces.\n");
			return (ERROR);
		}
		i++;
	}
	if (i < 5 || i > 11 || comma_counter != 2)
	{
		ft_printf(2, "Error\nInvalid RGB format, should be:");
		ft_printf(2, "[F-C] [0-255],[0-255,[0-255]]\n Whitespaces matter.\n");
		return (ERROR);
	}
	return (ft_parse1_util_check_valid_rgb2(line, rgb_slots));
}

//This function checks correct values for RGB numbers.
int	ft_parse1_util_check_valid_rgb2(char *line, int *rgb_slots)
{
	char	**split;
	int		index;

	index = 0;
	ft_printf(LOGS, "[PARSE1_UTIL]: Checking correct values for RGB\n");
	split = ft_split(line, ',');
	if (!split)
	{
		ft_printf(2, "Error\nAlloc error within split process in RGB check.\n");
		return (ERROR);
	}
	while (split[index])
	{
		if (ft_parse1_util_rgb_atoi(split[index], &rgb_slots[index]) == false)
		{
			ft_printf(2, "Error\nInvalid value for RGB. ([0-255])\n");
			ft_free_tab(split);
			return (ERROR);
		}
		index++;
	}
	ft_printf(LOGS, "[PARSE1_UTIL]: Valid RGB\n");
	ft_free_tab(split);
	return (0);
}

//This function verifies that a single value is a valid number between 0-255.
//increments the index <i> for further use in another call.
bool	ft_parse1_util_rgb_atoi(char *nptr, int *int_addr)
{
	int	i;

	i = 0;
	*int_addr = 0;
	if (!ft_isdigit(nptr[i]))
		return (false);
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		*int_addr = *int_addr * 10 + (nptr[i] - '0');
		i++;
	}
	if (*int_addr > 255 || (!ft_isdigit(nptr[i]) && nptr[i] != ','
			&& nptr[i] != '\0') || i > 3)
		return (false);
	return (true);
}
