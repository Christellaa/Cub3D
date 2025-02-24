/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse1_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 01:15:57 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/24 06:12:36 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

//This function takes <line> as argument
//It returns the cardinal direction that the line gives as an int.
int	ft_parse1_util_which_cardinal(char *line)
{
	ft_printf(LOGS, "[PARSE1_UTIL]: Finding specific cardinal\n");
	if (!ft_strncmp(line, "NO", 2))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found North\n");
		return (NORTH);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found South\n");
		return (SOUTH);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found East\n");
		return (EAST);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found West\n");
		return (WEST);
	}
	ft_printf(LOGS, "[PARSE1_UTIL]: Invalid line cardinal \n");
	return (-1);
}

//This function takes <line> as argument
//It returns whether the line is a floor or a ceiling as an int.
int	ft_parse1_util_which_fc(char *line)
{
	if (line[0] == 'F' && (ft_isdigit(line[1]) || ft_iswhitespace(line[1])))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found Floor\n");
		return (FLOOR);
	}
	else if (line[0] == 'C' && (ft_isdigit(line[1]) || ft_iswhitespace(line[1])))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found Ceiling\n");
		return (CEILING);
	}
	ft_printf(LOGS, "[PARSE1_UTIL]: Invalid line floor_ceiling got through\n");
	return (-1);
}

// Looks for the .xpm suffix at the end of a texture path.
int	ft_parse1_util_find_xpm(char *path)
{
	ft_printf(LOGS, "[PARSE1_UTIL]: Looking for .xpm suffix: %s\n", path);
	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4))
	{
		ft_printf(2, "Error\nTexture file must end by .xpm: %s", path);
		return (ERROR);
	}
	ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Found .xpm suffix\n");
	return (0);
}

//This function looks for duplicate lines, assigning a texture path to a cardinal line twice.
int	ft_parse1_util_find_duplicate_xpm(char *line, int num, t_data *data)
{
	ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Searching for duplicate for %s\n", line);
	if ((num == NORTH && data->north_txt != NULL)
		|| (num == SOUTH && data->south_txt != NULL)
		|| (num == EAST && data->east_txt != NULL)
		|| (num == WEST && data->west_txt != NULL))
	{
		ft_printf(2, "Error\nMultiple assignment of cardinal texture\n");
		return (ERROR);
	}
	ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: No duplicate assignment.\n");
	return (0);
}

//This function looks for duplicate lines, assigning RGB to floor or ceiling twice.
int	ft_parse1_util_find_duplicate_rgb(int num, t_data *data)
{
	if (num == FLOOR)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Checking for duplicate floor\n");
		if (data->floor_rgb->assigned == true)
			return (ERROR);
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: No duplicate floor found\n");
	}
	else if (num == CEILING)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: Checking for duplicate ceiling\n");
		if (data->ceiling_rgb->assigned == true)
			return (ERROR);
		ft_printf(LOGSV, "[VERBOSE][PARSE1_UTIL]: No duplicate ceiling found\n");
	}
	return (0);
}
