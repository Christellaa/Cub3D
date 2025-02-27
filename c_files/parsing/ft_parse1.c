/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:00:11 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/27 23:25:34 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

//This functions looks for the first three characters of a "Cardinal" line.
//If the line being read is a "Cardinal line", function returns the card value
//If the line being read is empty or full of spaces, returns 42
//Else returns -1
int	ft_parse1_search_cardinals(char *line)
{
	int	index;

	index = 0;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1]: Found a cardinal line\n");
		return (ft_parse1_util_which_cardinal(line));
	}
	if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1]: Found a ceiling/floor line\n");
		return (ft_parse1_util_which_fc(line));
	}
	while (line[index])
	{
		if (ft_iswhitespace(line[index]) || line[index] == '\n')
			index++;
		else
			return (ft_printf(2, "Error\nFound an invalid line\n"), ERROR);
	}
	if (line[index] == '\n' || line[index] == '\r' || line[index] == '\0')
		return (42);
	return (ERROR);
}

//This function takes the <line> as argument and verifies it follows rule.
//If it is, then it is assigned to the data struct.
int	ft_parse1_check_line(char *line, int num, t_data *data)
{
	ft_printf(LOGS, "[PARSE1]: Verifying line\n");
	if (num >= NORTH && num <= WEST)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1]: Verifying XPM path %s\n", line);
		return (ft_parse1_xpm_check(line, num, data));
	}
	else if (num == FLOOR || num == CEILING)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1]: Verifying RGB values %s\n", line);
		return (ft_parse1_rgb_check(line, num, data));
	}
	return (ERROR);
}

//This function verifies that the file in <line> is a path to a valid xpm file.
//It also verifies that there is no texture duplication for data.
//It then leads to data assignation
int	ft_parse1_xpm_check(char *line, int num, t_data *data)
{
	int	new_index;
	int	texture_fd;

	new_index = 2;
	while (ft_iswhitespace(line[new_index]))
		new_index++;
	ft_printf(LOGSV, "[VERBOSE][PARSE1]: xpm path is: %s\n", &line[new_index]);
	if (ft_parse1_util_find_xpm(&line[new_index]) == ERROR)
		return (ERROR);
	if (ft_parse1_util_find_duplicate_xpm(num, data) == ERROR)
		return (ERROR);
	texture_fd = open(&line[new_index], __O_DIRECTORY);
	if (texture_fd != -1)
	{
		ft_printf(2, "Error\nTexture path leads to directory\n");
		return (close(texture_fd), ERROR);
	}
	texture_fd = open(&line[new_index], O_RDONLY);
	if (texture_fd == -1)
	{
		ft_printf(2, "Error\n%s\n", strerror(errno));
		return (close(texture_fd), ERROR);
	}
	close(texture_fd);
	return (ft_parse2_assign_texture_to_data(&line[new_index], num, data));
}

//This function verifies that the RGB values for data are correct
// And that theyre not being assigned duplicatively
int	ft_parse1_rgb_check(char *line, int num, t_data *data)
{
	int	new_index;
	int	rgb_values[3];

	new_index = 1;
	while (ft_iswhitespace(line[new_index]))
		new_index++;
	ft_printf(LOGSV, "[VERBOSE][PARSE1]: RGB nums: %s\n", &line[new_index]);
	if (ft_parse1_util_find_duplicate_rgb(num, data) == ERROR)
	{
		ft_printf(2, "Error\nMultiple assignment of Floor/Ceiling\n");
		return (ERROR);
	}
	if (ft_parse1_util_check_valid_rgb(&line[new_index], rgb_values) == ERROR)
	{
		ft_printf(2, "Error\nInvalid RGB format given to Floor/Ceiling");
		return (ERROR);
	}
	return (ft_parse2_assign_rgb_to_data(data, rgb_values, num));
}
