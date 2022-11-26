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

void	init_move(t_move *move)
{
	move->pos.vx = 22.0;
	move->pos.vy = 11.5;
	move->dir.vx = 0.0;
	move->dir.vy = -1.0;
	move->plane.vx = 0.66;
	move->plane.vy = 0.0;
	move->moveSpeed = 0.05;
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
}

void	load_image(t_window *window, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(window->mlx, path, &img->img_width, &img->img_height);
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

void	load_texture(t_window *win)
{
	t_img	img;

	load_image(win, win->texture[0], "textures/eagle.xpm", &img);
	load_image(win, win->texture[1], "textures/redbrick.xpm", &img);
	load_image(win, win->texture[2], "textures/purplestone.xpm", &img);
	load_image(win, win->texture[3], "textures/greystone.xpm", &img);
	load_image(win, win->texture[4], "textures/bluestone.xpm", &img);
	load_image(win, win->texture[5], "textures/mossy.xpm", &img);
	load_image(win, win->texture[6], "textures/wood.xpm", &img);
	load_image(win, win->texture[7], "textures/colorstone.xpm", &img);
}
