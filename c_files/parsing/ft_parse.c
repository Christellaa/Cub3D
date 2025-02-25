/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:38:48 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/25 04:54:55 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks that the argument given is valid for the execution of cub3d.
// It may be cut into multiple different functions later for norm purposes.
int	ft_parse(char **argv, t_data *data)
{
	int	open_fd;
	char	*line;

	ft_printf(LOGS, "[PARSE]: Parsing the argument given\n");
	open_fd = ft_parse_check_file_path(argv, data);
	line = NULL;
	if (open_fd == ERROR)
		return (ERROR);
	if (ft_parse_check_file_rules(&line, open_fd, data) == ERROR)
		return (ERROR);
	if (ft_parse_check_map_rules(&line, open_fd, data) == ERROR)
		return(close(open_fd), ERROR);
	return (close(open_fd), 0);
}

// Verifies single argument with valid path and correct access rights.
// Returns file descriptor of the file on success, -1 on error (With printed message.)
// Function tested. Written to norm (without LOGSV).
int	ft_parse_check_file_path(char **argv, t_data *data)
{
	int	index;
	int	open_fd;

	ft_printf(LOGS, "[PARSE]: Verifying argument validity\n");
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying .cub extension: argv[1] == %s\n", argv[1]);
	index = ft_strlen(argv[1]) - 1;
	if (index <= 4)
	{
		ft_printf(2, "Error\nInvalid file format\nUsage: cub3d [map_file.cub]\n");
		return (ERROR);
	}
	if (argv[1][index] != 'b' || argv[1][index - 1] != 'u'
		|| argv[1][index - 2] != 'c' || argv[1][index - 3] != '.')
	{
		ft_printf(2, "Error\nInvalid file format\nUsage: cub3d [map_file.cub]\n");
		return (ERROR);
	}
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying access and path to file.\n");
	open_fd = open(argv[1], __O_DIRECTORY);
	if (open_fd != -1)
	{
		ft_printf(2, "Error\nCouldn't open file:is a directory");
		return (ERROR);
	}
	open_fd = open(argv[1], O_RDONLY);
	if (open_fd == ERROR)
		ft_printf(2, "Error\n%s\n", strerror(errno));
	data->filename = ft_strdup(argv[1]);
	if (!data->filename)
		return (ft_printf(2, "Error\nMalloc error during parsing\n"), ERROR);
	return (open_fd);
}

// This function verifies that the file has 6 lines in whatever order separated by however many empty lines.
// These lines contain the texture files for northern, southern, eastern and western walls.
// It verifies that there are 2 lines containing floor and ceiling colors in RGB.
// It verifies that there is a map (But doesn't verify the map_rules itself.)
// Returns (-1) on error, 0 on successful file.
int ft_parse_check_file_rules(char **line, int open_fd, t_data *data)
{
	int		all_cardinals;
	int		num;

	ft_printf(LOGS, "[PARSE]: Verifying file rules\n");
	all_cardinals = 0;
	*line = NULL;
	if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
		return (ERROR);
	while (*line && all_cardinals != 6)
	{
		ft_printf(LOGSV, "[VERBOSE][PARSE1]: Here is the current line: '%s'\n", *line);
		num = ft_parse1_search_cardinals(*line);
		if ((num >= NORTH && num <= WEST) || (num == FLOOR || num == CEILING))
		{
			ft_printf(LOGSV, "[VERBOSE][PARSE1]: Found a special line. Analysing path\n");
			if (ft_parse1_check_line(*line, num, data) == ERROR)
				num = ERROR;
			all_cardinals++;
		}
		free(*line);
		*line = NULL;
		if (num == ERROR)
			return (get_next_line(open_fd, 1), ERROR);
		if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
			return (ERROR);
	}
	if (all_cardinals != 6)
	{
		ft_printf(2, "Error\nMissing cardinal or floor/ceiling lign.\n");
		return (ERROR);
	}
	return (0);
}

//This function verifies that the map in <open_fd> obeys the map rules:
//Characters within are only: [1, 0, N, S, E, W, ' ']
//The map is closed and there are no whitespaces within the map visible by the player.
//The data from the map in <open_fd> can be assigned to <data> afterwards
int	ft_parse_check_map_rules(char **line, int open_fd, t_data *data)
{
	ft_printf(LOGS, "[PARSE]: Verifying Map Rules %s.\n", *line);
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying lines have valid chars\n");
	if (ft_parse3_assign_map_to_data(line, open_fd, data) == ERROR)
	{
		close(open_fd);
		ft_printf(2, "Error\nCouldn't retrieve player/map data");
		return (ERROR);
	}
	// ft_printf(LOGSV, "[VERBOSE][PARSE]: Closing and reopening fd to read map again\n");
	// close(open_fd);
	// open_fd = open(data->filename, O_RDONLY);
	// if (open_fd == -1)
	// {
	// 	ft_printf(2, "Error\nCouldn't open file\n");
	// 	return (ERROR);
	// }
	// else if (ft_parse3_flood_fill(open_fd) == ERROR)
	// {
	// 	close(open_fd);
	// 	ft_printf(2, "Error\nMap isn't closed/Found space inside\n");
	// 	return (ERROR);
	// }
	close(open_fd);
	return (0);
}
