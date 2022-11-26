#include "../includes/cub3d.h"

void	rotate(double *x, double *y, double angle)
{
	double	old;

	old = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = old * sin(angle) + *y * cos(angle);
}

void	rotate_my_view(t_move *move, double angle)
{
	rotate(&move->dir.vx, &move->dir.vy, angle);
	rotate(&move->plane.vx, &move->plane.vy, angle);
}

t_vec	plus_vector(t_vec a, t_vec b)
{
	t_vec	result;

	result.vx = a.vx + b.vx;
	result.vy = a.vy + b.vy;
	return (result);
}

t_vec	minus_vector(t_vec a, t_vec b)
{
	t_vec	result;

	result.vx = a.vx - b.vx;
	result.vy = a.vy - b.vy;
	return (result);
}

t_vec	multiple_vector(double k, t_vec a)
{
	t_vec	result;

	result.vx = k * a.vx;
	result.vy = k * a.vy;
	return (result);
}
