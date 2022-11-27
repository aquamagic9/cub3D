/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:19 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:00:46 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

int	set_texture(int ***texture)
{
	int	size;
	int	i;
	int	j;

	size = 11;
	*texture = (int **)malloc(sizeof(int *) * size);
	if (!*texture)
		return (-1);
	i = -1;
	while (++i < size)
	{
		(*texture)[i] = (int *)malloc(sizeof(int) * (TEX_HEIGHT * TEX_WIDTH));
		if (!*texture)
			return (-1);
	}
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < TEX_HEIGHT * TEX_WIDTH)
		(*texture)[i][j] = 0;
	}
	return (1);
}

void	draw_background(int **buf, int floorColor, int ceilColor)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
		{
			buf[y][x] = floorColor;
			buf[HEIGHT - y - 1][x] = ceilColor;
		}
	}
}

void	draw_texture(t_textureInfo *t, t_cal *cal, t_window *window, int x)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;

	tex_x = (int)(t->wall_x * (double)TEX_WIDTH);
	step = 1.0 * TEX_HEIGHT / t->line_height;
	tex_pos = (t->draw_start - HEIGHT / 2 + t->line_height / 2) * step;
	if (cal->side == 0 && cal->ray_dir.vx > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (cal->side == 1 && cal->ray_dir.vy < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	y = t->draw_start - 1;
	while (++y < t->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		window->buf[y][x] = \
			window->texture[t->texture_num][TEX_HEIGHT * tex_y + tex_x];
	}
}

void	put_texture(t_cal *cal, t_move *move, t_window *window, int x)
{
	t_textureInfo	t;

	t.line_height = (int)(HEIGHT / cal->perp_wall_dist);
	t.draw_start = -t.line_height / 2 + HEIGHT / 2;
	t.draw_end = t.line_height / 2 + HEIGHT / 2;
	if (t.draw_start < 0)
		t.draw_start = 0;
	if (t.draw_end >= HEIGHT)
		t.draw_end = HEIGHT - 1;
	if (cal->side == 0 && cal->ray_dir.vx > 0)
		t.texture_num = D_WEST;
	else if (cal->side == 0 && cal->ray_dir.vx <= 0)
		t.texture_num = D_EAST;
	else if (cal->side == 1 && cal->ray_dir.vy > 0)
		t.texture_num = D_NORTH;
	else if (cal->side == 1 && cal->ray_dir.vy <= 0)
		t.texture_num = D_SOUTH;
	if (cal->side == 0)
		t.wall_x = move->pos.vy + cal->perp_wall_dist * cal->ray_dir.vy;
	else
		t.wall_x = move->pos.vx + cal->perp_wall_dist * cal->ray_dir.vx;
	t.wall_x -= floor(t.wall_x);
	draw_texture(&t, cal, window, x);
}

void	draw(t_window *window)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			window->img.data[y * WIDTH + x] = window->buf[y][x];
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img.img, 0, 0);
}
