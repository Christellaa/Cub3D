/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 07:06:50 by ilevy             #+#    #+#             */
/*   Updated: 2025/03/13 13:32:21 by cde-sous         ###   ########.fr       */
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
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

// ------------DEFINE---------------

// Macros controlling the display of logs during program execution.
// Set LOGS to 2 for simple LOGS, LOGSV to 2 for verbose (With more details).
// Set LOGS and LOGSV to -1 to hide logs
# define LOGS -1
# define LOGSV -1
# define BONUS 0

# define ERROR -1

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define FLOOR 4
# define CEILING 5

# define WIDTH 1200
# define HEIGHT 800

# define USAGE "Error\nWrong args number.\nUsage: cub3D [map_file.cub]\n"
# define FILE_FORMAT "Error\nInvalid file format\nUsage: cub3D [map_file.cub]\n"
# define FILE_DIR "Error\nCouldn't open file: is a directory\n"

# define PI 3.1415926535
# define SPEED 0.015

// ------------TYPEDEF--------------

typedef struct s_rgb
{
	bool			assigned;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	bool		p_assigned;
	char		direction;
	int			map_x;
	int			map_y;
}	t_map;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_stack
{
	t_pos	*pos_data;
	int		top;
	int		max_size;
}	t_stack;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;

	double	dir_x;
	double	dir_y;
	double	old_dir_x;

	double	plane_x;
	double	plane_y;
	double	old_plane_x;

	double	camera_x;

	double	ray_dir_x;
	double	ray_dir_y;

	double	side_dist_x;
	double	side_dist_y;

	double	delta_dist_x;
	double	delta_dist_y;

	double	wall_x;

	double	perp_wall_dist;

	int		step_x;
	int		step_y;

	int		line_height;
	int		draw_start;
	int		draw_end;

	int		color;

	int		move_x;
	int		move_y;
	int		rotate;

}	t_player;

typedef struct s_mlx
{
	void	*mlx;

	void	*win;
	char	*name;
	int		width;
	int		height;
	void	*img_ptr;
	int		bpp;
	int		s_l;
	int		e;
	void	*buf;
}	t_mlx;

typedef struct s_texture
{
	char	*path_to_xpm;
	int		width;
	int		height;
	void	*img;
	char	*addr;
	int		bpp;
	int		s_l;
	int		e;
}	t_texture;

typedef struct s_minimap
{
	t_map	*map;
	void	*img_ptr;
	int		bpp;
	int		s_l;
	int		e;
	int		*buf;
	int		tile_size;
	int		margin;
}	t_minimap;

typedef struct s_data
{
	char		*filename;
	t_texture	*north_txt;
	t_texture	*south_txt;
	t_texture	*east_txt;
	t_texture	*west_txt;
	double		time;
	double		old_time;

	t_rgb		*floor_rgb;
	t_rgb		*ceiling_rgb;

	t_player	*player;

	t_map		*map;

	t_mlx		*mlx;
	t_minimap	*minimap;
}	t_data;

// ------------DECLARE--------------

// INITIALIZING

// 		ft_init.c
int			ft_init_data(t_data *data);
void		ft_init_data_params(t_data *data);
void		ft_init_map(t_map *map);
void		ft_init_player(t_player *player);
void		ft_init_rgbs(t_rgb *ceiling, t_rgb *floor);

//		ft_init_2.c
int			ft_init_mlx(t_mlx *mlx);
int			ft_init_minimap(t_data *data);
void		ft_init_dda(t_player *p, t_map *m, int x);
void		ft_init_dda2(t_player *p, t_map *m);

// PARSING

// 		ft_parse.c
int			ft_parse(char **argv, t_data *data);
int			ft_parse_check_file_path(char **argv, t_data *data);
int			ft_parse_check_file_rules(char **line, int fd, t_data *data,
				int card);
int			ft_parse_check_map_rules(char **line, int open_fd, t_data *data);

// 		ft_parse1.c
int			ft_parse1_search_cardinals(char *line);
int			ft_parse1_check_line(char *line, int return_num, t_data *data);
int			ft_parse1_xpm_check(char *line, int num, t_data *data);
int			ft_parse1_rgb_check(char *line, int num, t_data *data);

// 		ft_parse2.c
int			ft_parse2_assign_texture_to_data(char *path, int num, t_data *data);
t_texture	*init_texture(char *path, t_mlx *mlx);
int			ft_parse2_assign_rgb_to_data(t_data *data, int *rgb_values,
				int num);

//		ft_parse3.c
int			ft_parse3_assign_map_to_data(char **line, int open_fd,
				t_data *data);
int			ft_parse3_flood_fill(t_data *data);

// EXEC

//		ft_try_raycaster.c
void		ft_raycaster(t_data *data);
void		ft_digital_differential_analyzer(t_player *p, t_map *m, int *hit,
				int *side);
void		ft_calculate_line_height(t_player *p, t_data *data, int side);
void		ft_init_wall_x(t_data *data, int side);

//		draw_ceiling_floor.c
void		ft_draw_ceiling_floor(t_data *data);
void		init_colors(int *c_color, int *f_color, t_data *data);
void		ft_draw_ceiling_floor2(t_data *data, int pixel_index);

//		draw_wall.c
void		ft_draw_vertical(int x, t_player *p, t_data *data, int *side);
t_texture	*ft_get_texture(t_player *p, t_data *data, int *side);
void		ft_draw_vertical2(t_player *p, double txt_pos, t_texture *texture,
				int txt_x);
int			ft_get_txt_pixel(t_texture *txt, int x, int y);
void		ft_put_pixel(t_data *data, int x, int y, int color);

//		minimap? // ft_window.c
void		put_pixel(t_data *data, int x, int y, int color);
void		render_map2D(t_minimap *minimap, t_data *data);

// UTILS

//		ft_parse1_utils.c
int			ft_parse1_util_which_cardinal(char *line);
int			ft_parse1_util_which_fc(char *line);
int			ft_parse1_util_find_xpm(char *path);
int			ft_parse1_util_find_duplicate_xpm(int num, t_data *data);
int			ft_parse1_util_find_duplicate_rgb(int num, t_data *data);

//		ft_parse1_utils_2.c
int			ft_parse1_util_check_valid_rgb(char *line, int *rgb_slots);
int			ft_parse1_util_check_valid_rgb2(char *line, int *rgb_slots);
bool		ft_parse1_util_rgb_atoi(char *nptr, int *int_addr);

//		ft_parse3_utils.c
int			ft_parse3_util_skip_whitespaces(char **line, int open_fd);
int			ft_parse3_util_skip_to_map(char **line, int temp_fd);
int			ft_parse3_util_skip_one(char *line);
int			ft_parse3_util_alloc_map_memory(char **line, int fd, t_data *data);
int			ft_parse3_util_is_invalid_line(char **line);

//		ft_parse3_utils_2.c
int			ft_parse3_util2_initialize_map(char **line, int open_fd,
				t_data *data);
int			ft_parse3_util2_single_player(t_data *data);
int			ft_p3_isp(char c, t_map *map, int x, int y);
int			ft_parse3_util2_check_map_closed(t_map *map);

//		ft_flood_fill_util.c
bool		ft_ff_util_is_empty(t_stack *stack);
int			ft_flood_fill_one(t_stack *stack, t_map *map, int *dir_x,
				int *dir_y);
t_pos		ft_ff_util_pop(t_stack *stack, int *i);
int			ft_flood_fill_check_char(int new_y, int new_x, t_map *map);
void		ft_ff_util_push(t_stack *stack, int x, int y);

//		ft_utils.c
int			ft_util_is_whitespace_only(char **line);
int			ft_util_safe_gnl(char **line, int fd, int mode);
int			*ft_util_get_dir_y(void);
int			*ft_util_get_dir_x(void);

//		ft_hooks.c
int			ft_cross(t_data *data);
int			ft_key_press_handler(int keycode, t_data *data);
int			ft_key_release_handler(int keycode, t_data *data);
int			render(t_data *data);

//		ft_moves_utils.c
int			move_player_forward(t_data *data);
int			move_player_backward(t_data *data);
int			move_player_left(t_data *data);
int			move_player_right(t_data *data);

//		ft_moves.c
int			move_player(t_data *data);
int			rotate_player(t_data *data, double rotation);
int			is_move_valid(t_data *data, double new_x, double new_y);
int			is_move_in_map(t_map *map, double x, double y);

// FREE

//		ft_free.c
void		ft_clean_exit(t_data *data, int errcode);
void		ft_free_textures(t_data *data);
void		ft_free_maps(t_data *data);
void		ft_free_mlx(t_data *data);

//		ft_free_utils.c
void		ft_free_tab(char **split);
void		safe_free_texture(t_texture *txt, t_mlx *mlx);

// MAIN

void		init_player_direction(t_data *data);
void		hooks(t_data *data);

#endif
