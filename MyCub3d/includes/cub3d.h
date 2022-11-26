#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define texWidth 64
# define texHeight 64
# define mapWidth 24
# define mapHeight 24
# define width 640
# define height 480

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
	double	X;
	double	Y;
}			t_pair;


typedef struct s_pairInt
{
	int	X;
	int	Y;
}			t_pairInt;

typedef struct s_cal
{
	t_vec	rayDir;
	t_pairInt	map;
	t_pair sideDist;
	t_pair deltaDist;
	t_pair step;
	double perpWallDist;
	int		side;
}			t_cal;

typedef struct s_textureInfo
{
	int lineHeight;
	int drawStart;
	int drawEnd;
	int textureNum;
	double wallX;
	int texX;
}			t_textureInfo;

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct	s_key
{
	int		key_a;
	int		key_w;
	int		key_s;
	int		key_d;
	int		key_left;
	int		key_right;
	int		key_esc;
}				t_key;

typedef struct s_move
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
	double	moveSpeed;
	double	rotSpeed;
}				t_move;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	t_img	img; // TODO: NEED MODIFY
	int		buf[height][width];
	int		**texture;
}				t_window;

typedef struct	s_info
{
	t_key		key;
	t_move		move;
	t_window	window;
  	char 		**texture_file;
	int			worldMap[mapWidth][mapHeight];
}				t_info;

//vector_utils.c
void rotate(double *x, double *y, double angle);
void	rotate_my_view(t_move *move, double angle);
t_vec plus_vector(t_vec a, t_vec b);
t_vec minus_vector(t_vec a, t_vec b);
t_vec multiple_vector(double k, t_vec a);

//draw.c
int set_texture(int ***texture);
void draw_background(int buf[height][width], int floorColor, int ceilColor);
void	draw_texture(t_textureInfo *t, t_cal *cal, t_window *window, int x);
void	put_texture(t_cal *cal, t_move *move, t_window *window, int worldMap[mapWidth][mapHeight], int x);
void	draw(t_window *window);

//key.c
int	key_release(int key, t_key *key_state);
void	key_update(t_key *key, t_move *move, int worldMap[mapWidth][mapHeight]);
int	key_press(int key, t_key *key_state);

//init.c
void init(t_info *info);
void	load_image(t_window *window, int *texture, char *path, t_img *img);
void	load_texture(t_window *win);

//raycasting.c
void	find_perp_wall_dist(t_cal *cal, int worldMap[mapWidth][mapHeight]);
void	find_distance(t_cal *cal, t_vec pos);
void	ray_casting(t_move *move, t_window *window, int worldMap[mapWidth][mapHeight]);

// parse.c
void  open_file_with_validate(char *file_path);

void  exit_with_error(char *str);

#endif