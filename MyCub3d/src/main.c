#include "../includes/cub3d.h"

t_vec normalize(t_vec a)
{
	double absV;

	absV = sqrt(a.vx * a.vx + a.vy * a.vy);
	a.vx = a.vx / absV;
	a.vy = a.vy / absV;
	return a; 
}

double findRadianBetweenTwoVec(t_vec v1, t_vec v2)
{
	return (fabs(acos((v1.vx * v2.vx + v1.vy * v2.vy)
		/ (sqrt(v1.vx * v1.vx + v1.vy * v1.vy) * sqrt(v2.vx * v2.vx + v2.vy * v2.vy)))));
}

double findRadianBetweenTwoVec2(t_vec v1, t_vec v2)
{
	return (fabs((v1.vx * v2.vx + v1.vy * v2.vy)
		/ (sqrt(v1.vx * v1.vx + v1.vy * v1.vy) * sqrt(v2.vx * v2.vx + v2.vy * v2.vy))));
}

int	main_loop(t_info *info)
{
	draw_background(info->buf, 220*65536 + 100*256 + 0, 225*65536 + 30*256 + 0);
	ray_casting(info);
	draw(info);
	key_update(info);
	return (0);
}

int	main(void)
{
	t_info info;

	int world[mapWidth][mapHeight] = {
				{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
				{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
				{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
				{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
				{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
				{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
				{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
				{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
				{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
				{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
				{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
				{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
				{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
				{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
				{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
				{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
				{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
				{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
				{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
				{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
				{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
				{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
				{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
				{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
	};
	for(int i = 0 ; i < mapWidth; i++)
	{
		for (int j = 0 ; j < mapHeight; j++)
		{
			info.worldMap[i][j] = world[i][j];
		}
	}
	init(&info);
	if (!set_texture(&info.texture))
		return (0);
	load_texture(&info);
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}