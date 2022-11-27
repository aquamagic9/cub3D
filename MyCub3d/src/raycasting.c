#include "../includes/cub3d.h"

void	find_perp_wall_dist(t_cal *cal, int **worldMap)
{
	while (1)
	{
		if (worldMap[cal->map.Y][cal->map.X] > 0)
			break ;
		if (cal->sideDist.X < cal->sideDist.Y)
		{
			cal->sideDist.X += cal->deltaDist.X;
			cal->map.X += cal->step.X;
			cal->side = 0;
		}
		else
		{
			cal->sideDist.Y += cal->deltaDist.Y;
			cal->map.Y += cal->step.Y;
			cal->side = 1;
		}
	}
	if (cal->side == 0)
		cal->perpWallDist = cal->sideDist.X - cal->deltaDist.X;
	else
		cal->perpWallDist = cal->sideDist.Y - cal->deltaDist.Y;
}

void	find_distance(t_cal *cal, t_vec pos)
{
	cal->deltaDist.X = fabs(1 / cal->rayDir.vx);
	cal->deltaDist.Y = fabs(1 / cal->rayDir.vy);
	if (cal->rayDir.vx < 0)
	{
		cal->step.X = -1;
		cal->sideDist.X = (pos.vx - cal->map.X) * cal->deltaDist.X;
	}
	else
	{
		cal->step.X = 1;
		cal->sideDist.X = (cal->map.X + 1.0 - pos.vx) * cal->deltaDist.X;
	}
	if (cal->rayDir.vy < 0)
	{
		cal->step.Y = -1;
		cal->sideDist.Y = (pos.vy - cal->map.Y) * cal->deltaDist.Y;
	}
	else
	{
		cal->step.Y = 1;
		cal->sideDist.Y = (cal->map.Y + 1.0 - pos.vy) * cal->deltaDist.Y;
	}
}

void	ray_casting(t_move *move, t_window *window, int **worldMap)
{
	int		x;
	double	camera_x;
	t_cal	cal;

	x = -1;
	while (++x < width)
	{
		camera_x = 2 * x / (double)width - 1;
		cal.rayDir = plus_vector(move->dir, multiple_vector(camera_x, move->plane));
		cal.map.X = (int)move->pos.vx;
		cal.map.Y = (int)move->pos.vy;
		find_distance(&cal, move->pos);
		find_perp_wall_dist(&cal, worldMap);
		put_texture(&cal, move, window, x);
	}
}
