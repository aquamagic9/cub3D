/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:11 by junseo            #+#    #+#             */
/*   Updated: 2022/11/27 21:55:25 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_buf(int ***buf)
{
	int	i;

	*buf = (int **)malloc(sizeof(int *) * HEIGHT);
	if (*buf == NULL)
		exit_with_error("malloc fail!\n");
	i = -1;
	while (++i < HEIGHT)
	{
		(*buf)[i] = (int *)malloc(sizeof(int) * WIDTH);
		if ((*buf)[i] == NULL)
			exit_with_error("During Malloc");
		ft_memset((*buf)[i], 0, sizeof(int) * WIDTH);
	}
}

void	init_move(t_move *move)
{
	move->pos.vx = -1.0;
	move->pos.vy = -1.0;
	move->dir.vx = 0.0;
	move->dir.vy = -1.0;
	move->plane.vx = 0.66;
	move->plane.vy = 0.0;
	move->move_speed = 0.051;
	move->rot_speed = 0.05;
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
	if (window->mlx == NULL)
		exit_with_error("Mlx is not allocated\n");
	window->win = mlx_new_window(window->mlx, WIDTH, HEIGHT, "mlx");
	if (window->win == NULL)
		exit_with_error("Window is not allocated\n");
	window->img.img = mlx_new_image(window->mlx, WIDTH, HEIGHT);
	if (window->img.img == NULL)
		exit_with_error("Img is not allocated\n");
	window->img.data = (int *)mlx_get_data_addr(window->img.img, \
			&window->img.bpp, &window->img.size_l, &window->img.endian);
}

void	init(t_info *info)
{
	init_move(&info->move);
	init_key(&info->key);
	init_window(&info->window);
	set_buf(&info->window.buf);
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
