#include "../includes/cub3d.h"

void	set_buf(int buf[height][width])
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
		{
			buf[i][j] = 0;
		}
	}
}

void	set_color(t_color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

int	switch_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

void	init_move(t_move *move)
{
	move->pos.vx = -1.0;
	move->pos.vy = -1.0;
	move->dir.vx = 0.0;
	move->dir.vy = -1.0;
	move->plane.vx = 0.66;
	move->plane.vy = 0.0;
	move->moveSpeed = 0.051;
	move->rotSpeed = 0.05;
}

void	init_key(t_key *key)
{
	key->key_a = 0;
	key->key_w = 0;
	key->key_s = 0;
	key->key_d = 0;
	key->key_left = 0;
	key->key_right = 0;
	key->key_esc = 0;
}

void	init_window(t_window *window)
{
	window->mlx = mlx_init();
	printf("window->mlx:: %p !\n", window->mlx);
	window->win = mlx_new_window(window->mlx, width, height, "mlx");
	window->img.img = mlx_new_image(window->mlx, width, height);
	window->img.data = (int *)mlx_get_data_addr(window->img.img, &window->img.bpp, &window->img.size_l, &window->img.endian);
}

void	init(t_info *info)
{
	init_move(&info->move);
	init_key(&info->key);
	init_window(&info->window);
	set_buf(info->window.buf);
	// TODO: 개선 필요 하드코딩함
	info->texture_file = (char **)malloc(sizeof(char *) * 4);
	ft_bzero(info->texture_file, sizeof(char *) * 4);
	info->color_set = malloc(sizeof(t_color) * 2);
	set_color(&info->color_set[Z_CEILING], -1, -1, -1);
	set_color(&info->color_set[Z_FLOOR], -1, -1, -1);
	info->map_height = 0;
	info->map_width = 0;
	info->map_start_index = 0;
	ft_bzero(info->texture_file, sizeof(char *) * 4);
}

void	load_image(t_window *window, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	printf("MLX !!!!!!!!!!!%p\n", window->mlx);
	img->img = mlx_xpm_file_to_image(window->mlx, path, &img->img_width, &img->img_height);
	if (img->img == NULL)
		exit_with_error("error occurred during read image file");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(window->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(&info->window, info->window.texture[D_NORTH], info->texture_file[D_NORTH], &img);
	load_image(&info->window, info->window.texture[D_SOUTH], info->texture_file[D_SOUTH], &img);
	load_image(&info->window, info->window.texture[D_EAST], info->texture_file[D_EAST], &img);
	load_image(&info->window, info->window.texture[D_WEST], info->texture_file[D_WEST], &img);
	// load_image(win, win->texture[4], "textures/bluestone.xpm", &img);
	// load_image(win, win->texture[5], "textures/mossy.xpm", &img);
	// load_image(win, win->texture[6], "textures/wood.xpm", &img);
	// load_image(win, win->texture[7], "textures/colorstone.xpm", &img);
}
