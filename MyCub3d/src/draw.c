#include "../includes/cub3d.h"

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
		(*texture)[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth));
		if (!*texture)
			return (-1);
	}
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < texHeight * texWidth)
		(*texture)[i][j] = 0;
	}
	return (1);
}

void	draw_background(int buf[height][width], int floorColor, int ceilColor)
{
	int	x;
	int	y;

	y = -1;
	while (++y < height / 2)
	{
		x = -1;
		while (++x < width)
		{
			buf[y][x] = floorColor;
			buf[height - y - 1][x] = ceilColor;
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

	tex_x = (int)(t->wallX * (double)texWidth);
	step = 1.0 * texHeight / t->lineHeight;
	tex_pos = (t->drawStart - height / 2 + t->lineHeight / 2) * step;
	if (cal->side == 0 && cal->rayDir.vx > 0)
		tex_x = texWidth - tex_x - 1;
	if (cal->side == 1 && cal->rayDir.vy < 0)
		tex_x = texWidth - tex_x - 1;
	y = t->drawStart - 1;
	while (++y < t->drawEnd)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos += step;
		if (cal->side == 1)
			window->buf[y][x] = (window->texture[t->textureNum][texHeight * tex_y + tex_x] >> 1) & 8355711;
		else
			window->buf[y][x] = window->texture[t->textureNum][texHeight * tex_y + tex_x];
	}
}

void	put_texture(t_cal *cal, t_move *move, t_window *window, int worldMap[mapWidth][mapHeight], int x)
{
	t_textureInfo	t;

	t.lineHeight = (int)(height / cal->perpWallDist);
	t.drawStart = -t.lineHeight / 2 + height / 2;
	t.drawEnd = t.lineHeight / 2 + height / 2;
	if (t.drawStart < 0)
		t.drawStart = 0;
	if (t.drawEnd >= height)
		t.drawEnd = height - 1;
	
	t.textureNum = worldMap[cal->map.X][cal->map.Y] - 1; // TODO(hyuncho) : 나중에 삭제
	if (cal->side == 0 && cal->rayDir.vx > 0)
		t.textureNum = 1;//서
	else if (cal->side == 0 && cal->rayDir.vx <= 0)
		t.textureNum = 4;//동
	else if (cal->side == 1 && cal->rayDir.vy > 0)
		t.textureNum = 2;//북
	else if (cal->side == 1 && cal->rayDir.vy <= 0)
		t.textureNum = 3;//남

	if (cal->side == 0)
		t.wallX = move->pos.vy + cal->perpWallDist * cal->rayDir.vy;
	else
		t.wallX = move->pos.vx + cal->perpWallDist * cal->rayDir.vx;
	t.wallX -= floor(t.wallX);
	draw_texture(&t, cal, window, x);
}

void	draw(t_window *window)
{
	int	x;
	int	y;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			window->img.data[y * width + x] = window->buf[y][x];
	}
	mlx_put_image_to_window(window->mlx, window->win, window->img.img, 0, 0);
}
