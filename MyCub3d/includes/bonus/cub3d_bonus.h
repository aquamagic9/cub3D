/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:56:17 by junseo            #+#    #+#             */
/*   Updated: 2022/11/27 23:59:41 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../../mlx/mlx.h"
# include "../../libft/includes/libft.h"
# include "../../libft/includes/get_next_line.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define WIDTH 640
# define HEIGHT 480
# define PI 3.141592

# define K_A 0
# define K_S 1
# define K_D 2
# define K_W 13
# define K_LEFT 123
# define K_RIGHT 124
# define K_ESC 53
# define BUTTON_CLOSE 17

enum e_texture
{
	T_ERROR = -1,
	T_NO,
	T_SO,
	T_WE,
	T_EA,
	T_FLOOR,
	T_CEIL,
	T_MAP,
	T_EMPTY
};

enum e_direction
{
	D_NORTH,
	D_SOUTH,
	D_WEST,
	D_EAST
};

enum e_map
{
	M_BLANK,
	M_WALL,
	M_VOID
};

enum e_zAxis
{
	Z_CEILING,
	Z_FLOOR
};

typedef struct s_vec
{
	double	vx;
	double	vy;
}			t_vec;

typedef struct s_pair
{
	double	x;
	double	y;
}			t_pair;

typedef struct s_pairInt
{
	int	x;
	int	y;
}	t_pairInt;

typedef struct s_cal
{
	t_vec		ray_dir;
	t_pairInt	map;
	t_pair		side_dist;
	t_pair		delta_dist;
	t_pair		step;
	double		perp_wall_dist;
	int			side;
}			t_cal;

typedef struct s_textureInfo
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		texture_num;
	double	wall_x;
	int		tex_x;
}			t_textureInfo;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}			t_img;

typedef struct s_key
{
	int	key_a;
	int	key_w;
	int	key_s;
	int	key_d;
	int	key_left;
	int	key_right;
	int	key_esc;
}			t_key;

typedef struct s_move
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	double	move_speed;
	double	rot_speed;
}			t_move;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		**buf;
	int		**texture;
}			t_window;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_info
{
	t_key		key;
	t_move		move;
	t_window	window;
	char		**texture_file;
	t_color		*color_set;
	int			map_width;
	int			map_height;
	int			map_start_index;
	int			**world_map;
}			t_info;

// vector_utils.c
void	rotate(double *x, double *y, double angle);
void	rotate_my_view(t_move *move, double angle);
t_vec	plus_vector(t_vec a, t_vec b);
t_vec	minus_vector(t_vec a, t_vec b);
t_vec	multiple_vector(double k, t_vec a);

// draw.c
int		set_texture(int ***texture);
void	draw_background(int **buf, int floorColor, int ceilColor);
void	draw_texture(t_textureInfo *t, t_cal *cal, t_window *window, int x);
void	put_texture(t_cal *cal, t_move *move, t_window *window, int x);
void	draw(t_window *window);

// key.c
int		key_release(int key, t_key *key_state);
void	key_update(t_key *key, t_move *move, int **world_map);
int		key_press(int key, t_key *key_state);

// load.c
void	set_color(t_color *color, int r, int g, int b);
int		switch_color(t_color color);
void	load_image(t_window *window, int *texture, char *path, t_img *img);
void	load_texture(t_info *info);

// init.c
void	init(t_info *info);

// raycasting.c
void	find_perp_wall_dist(t_cal *cal, int **world_map);
void	find_distance(t_cal *cal, t_vec pos);
void	ray_casting(t_move *move, t_window *window, int **world_map);

// parse.c
void	open_file_with_validate(char *file_path, t_info *info);
int		recovery(t_info *info);

// map.c
void	malloc_map(t_info *info);
int		record_map_data(char *line, t_info *info);
int		save_map(char *file_path, t_info *info);

// config_setter.c
int		save_wall_texture(char *line, enum e_direction direction, t_info *info);
int		save_ceil_floor_color(char *value, enum e_zAxis z, t_info *info);
int		set_player_pos_direction(t_move *move, char dir, \
	int width_index, int height_index);

// validation.c
int		is_valid_map_line(char *line);
void	file_extention_validator(char *file_name);
int		validation_map(t_info *info);
int		validation_config(t_info *info);

// error.c
void	exit_with_error(char *str);

// utils.c
char	*get_next_line_without_nl(int fd);
int		ft_close(int fd);
int		ft_open(char *str);
int		free_split(char **split);
int		jump(int fd, t_info *info);

#endif