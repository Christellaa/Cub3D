/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilevy <ilevy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:06:50 by ilevy             #+#    #+#             */
/*   Updated: 2025/02/23 00:48:56 by ilevy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//-------------INCLUDE--------------

# include "../libft/h_files/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

// ------------DEFINE---------------

// Macros controlling the display of logs during program execution.
// Set LOGS to 2 for simple LOGS, LOGSV to 2 for verbose (With more details).
// Set LOGS and LOGSV to -1 to hide logs
# define LOGS 2
# define LOGSV 2

# define ERROR -1

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define FLOOR 4
# define CEILING 5

// ------------TYPEDEF--------------

typedef struct s_rgb
{
	bool			assigned;
	unsigned char	R;
	unsigned char	G;
	unsigned char	B;
}t_rgb;

typedef struct s_data
{
	char	*north_txt;
	char	*south_txt;
	char	*east_txt;
	char	*west_txt;
	t_rgb	floor_rgb;
	t_rgb	ceiling_rgb;
}t_data;

// ------------DECLARE--------------

// PARSING

// ft_parse.c
int 	ft_parse(int argc, char **argv, t_data *data);
int 	ft_parse_check_file_path(int argc, char **argv);
int		ft_parse_check_file_rules(int open_fd, t_data *data);

// ft_parse1.c
int		ft_parse1_search_cardinals(char *line);
int		ft_parse1_check_line(char *line, int return_num, t_data *data);
int		ft_parse1_xpm_check(char *line, int num, t_data *data);
int		ft_parse1_rgb_check(char *line, int num, t_data *data);

// ft_parse2.c
int		ft_parse2_assign_texture_to_data(char *path, t_data *data);

// EXEC

// UTILS

// ft_parse1_utils.c
int		ft_parse1_util_which_cardinal(char *line);
int		ft_parse1_util_which_FC(char *line);
int		ft_parse1_util_find_xpm(char *path);
int		ft_parse1_util_find_duplicate_xpm(char *line, int num, t_data *data);
int		ft_parse1_util_find_duplicate_rgb(int num, t_data *data);

int		ft_parse1_util_check_valid_rgb(char *line, int *rgb_slots);
int		ft_parse1_util_check_valid_rgb2(char *line, int *rgb_slots);
bool	ft_parse1_util_rgb_atoi(char *nptr, int *int_addr);

// FREE
void	ft_free_tab(char **split);

// MAIN
#endif
