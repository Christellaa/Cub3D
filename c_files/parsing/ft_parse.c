/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:38:48 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/28 03:35:20 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../h_files/cub3d.h"

// This function checks that the argument given is valid for the exec of cub3d.
// It may be cut into multiple different functions later for norm purposes.
int	ft_parse(char **argv, t_data *data)
{
	int		open_fd;
	char	*line;

	ft_printf(LOGS, "[PARSE]: Parsing the argument given\n");
	open_fd = ft_parse_check_file_path(argv, data);
	line = NULL;
	if (open_fd == ERROR)
		return (ERROR);
	if (ft_parse_check_file_rules(&line, open_fd, data, 0) == ERROR)
		return (ERROR);
	if (ft_parse_check_map_rules(&line, open_fd, data) == ERROR)
		return (close(open_fd), ERROR);
	ft_printf(LOGS, "[PARSE]: Parsing complete. File is valid!\n");
	return (close(open_fd), 0);
}

// Verifies single argument with valid path and correct access rights.
// Returns fd of the file on success, -1 on error (With printed message.)
// Function tested. Written to norm (without LOGSV).
int	ft_parse_check_file_path(char **argv, t_data *data)
{
	size_t	index;
	int		open_fd;

	ft_printf(LOGS, "[PARSE]: Verifying argument validity\n");
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying .cub suffix:%s\n", argv[1]);
	index = ft_strlen(argv[1]) - 1;
	if (index < 4)
		return (ft_printf(2, FILE_FORMAT), ERROR);
	if (ft_strncmp((argv[1] + ft_strlen(argv[1]) - 4), ".cub", 4))
		return (ft_printf(2, FILE_FORMAT), ERROR);
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying access and path to file.\n");
	open_fd = open(argv[1], __O_DIRECTORY);
	if (open_fd != -1)
		return (close(open_fd), ft_printf(2, FILE_DIR), ERROR);
	open_fd = open(argv[1], O_RDONLY);
	if (open_fd == ERROR)
		ft_printf(2, "Error\n%s\n", strerror(errno));
	data->filename = ft_strdup(argv[1]);
	if (!data->filename)
		return (ft_printf(2, "Error\nMalloc error during parsing\n"), ERROR);
	return (open_fd);
}

// This function checks that there are 6 lines in whatever order n empty lines.
// These lines contain the texture files for north, south, east and west walls.
// It verifies that there are 2 lines containing floor and ceiling RGB.
// It verifies that there is a map (But doesn't verify the map_rules itself.)
// Returns (-1) on error, 0 on successful file.
int	ft_parse_check_file_rules(char **line, int open_fd, t_data *data, int card)
{
	int		num;

	*line = NULL;
	if (ft_util_safe_gnl(line, open_fd, 0) == ERROR)
		return (get_next_line(open_fd, 1), close(open_fd), ERROR);
	while (*line && card != 6)
	{
		num = ft_parse1_search_cardinals(*line);
		if ((num >= NORTH && num <= WEST) || (num == FLOOR || num == CEILING))
		{
			num = ft_parse1_check_line(*line, num, data);
			card++;
		}
		free(*line);
		*line = NULL;
		if (num == ERROR || ft_util_safe_gnl(line, open_fd, 0) == ERROR)
			return (get_next_line(open_fd, 1), close(open_fd), ERROR);
	}
	if (card != 6)
	{
		ft_printf(2, "Error\nMissing cardinal or floor/ceiling lign.\n");
		return (get_next_line(open_fd, 1), close(open_fd), ERROR);
	}
	return (0);
}

//This function verifies that the map in <open_fd> obeys the map rules:
//Characters within are only: [1, 0, N, S, E, W, ' ']
//The map is closed and there are no whitespaces visible by the player.
//The data from the map in <open_fd> can be assigned to <data> afterwards
int	ft_parse_check_map_rules(char **line, int open_fd, t_data *data)
{
	ft_printf(LOGS, "[PARSE]: Verifying Map Rules %s.\n", *line);
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Verifying lines have valid chars\n");
	if (ft_parse3_assign_map_to_data(line, open_fd, data) == ERROR)
		return (ERROR);
	ft_printf(LOGS, "[PARSE]: Stored map in t_map struct\n");
	ft_printf(LOGSV, "[VERBOSE][PARSE]: Performing flood_fill algorithm\n");
	if (ft_parse3_flood_fill(data) == ERROR)
		return (ERROR);
	return (0);
}
