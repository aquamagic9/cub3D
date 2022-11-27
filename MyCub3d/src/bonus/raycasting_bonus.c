/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:43 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:01:08 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

void	find_perp_wall_dist(t_cal *cal, int **world_map)
{
	while (1)
	{
		if (world_map[cal->map.y][cal->map.x] > 0)
			break ;
		if (cal->side_dist.x < cal->side_dist.y)
		{
			cal->side_dist.x += cal->delta_dist.x;
			cal->map.x += cal->step.x;
			cal->side = 0;
		}
		else
		{
			cal->side_dist.y += cal->delta_dist.y;
			cal->map.y += cal->step.y;
			cal->side = 1;
		}
	}
	if (cal->side == 0)
		cal->perp_wall_dist = cal->side_dist.x - cal->delta_dist.x;
	else
		cal->perp_wall_dist = cal->side_dist.y - cal->delta_dist.y;
}

void	find_distance(t_cal *cal, t_vec pos)
{
	cal->delta_dist.x = fabs(1 / cal->ray_dir.vx);
	cal->delta_dist.y = fabs(1 / cal->ray_dir.vy);
	if (cal->ray_dir.vx < 0)
	{
		cal->step.x = -1;
		cal->side_dist.x = (pos.vx - cal->map.x) * cal->delta_dist.x;
	}
	else
	{
		cal->step.x = 1;
		cal->side_dist.x = (cal->map.x + 1.0 - pos.vx) * cal->delta_dist.x;
	}
	if (cal->ray_dir.vy < 0)
	{
		cal->step.y = -1;
		cal->side_dist.y = (pos.vy - cal->map.y) * cal->delta_dist.y;
	}
	else
	{
		cal->step.y = 1;
		cal->side_dist.y = (cal->map.y + 1.0 - pos.vy) * cal->delta_dist.y;
	}
}

void	ray_casting(t_move *move, t_window *window, int **world_map)
{
	int		x;
	double	camera_x;
	t_cal	cal;

	x = -1;
	while (++x < WIDTH)
	{
		camera_x = 2 * x / (double)WIDTH - 1;
		cal.ray_dir = plus_vector(move->dir, \
				multiple_vector(camera_x, move->plane));
		cal.map.x = (int)move->pos.vx;
		cal.map.y = (int)move->pos.vy;
		find_distance(&cal, move->pos);
		find_perp_wall_dist(&cal, world_map);
		put_texture(&cal, move, window, x);
	}
}
