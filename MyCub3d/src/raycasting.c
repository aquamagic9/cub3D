#include "../includes/cub3d.h"

void	find_perp_wall_dist(t_cal *cal, t_info *info)
{
	while (1)
	{
		if (info->worldMap[cal->map.X][cal->map.Y] > 0)
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

void	ray_casting(t_info *info)
{
	int		x;
	double	camera_x;
	t_cal	cal;

	x = -1;
	while (++x < width)
	{
		camera_x = 2 * x / (double)width - 1;
		cal.rayDir = plus_vector(info->dir, multiple_vector(camera_x, info->plane));
		cal.map.X = (int)info->pos.vx;
		cal.map.Y = (int)info->pos.vy;
		find_distance(&cal, info->pos);
		find_perp_wall_dist(&cal, info);
		put_texture(&cal, info, x);
	}
}
