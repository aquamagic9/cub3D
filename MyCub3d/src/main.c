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
	
	draw_background(info->window.buf, switch_color(info->color_set[Z_FLOOR]), switch_color(info->color_set[Z_CEILING]));
	ray_casting(&info->move, &info->window, info->worldMap);
	draw(&info->window);
	key_update(&info->key, &info->move, info->worldMap);
	return (0);
}

int	exit_button_close()
{
	//free처리
	exit(1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info info;

	if (argc != 2)
		exit_with_error("Invalid argc");
	// int world[mapWidth][mapHeight] = {
	// 			{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
	// 			{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	// 			{8,0,3,0,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
	// 			{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
	// 			{8,0,3,0,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
	// 			{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
	// 			{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
	// 			{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
	// 			{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
	// 			{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
	// 			{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
	// 			{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
	// 			{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
	// 			{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
	// 			{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	// 			{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
	// 			{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
	// 			{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
	// 			{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	// 			{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	// 			{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	// 			{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
	// 			{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
	// 			{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
	// };
	// for(int i = 0 ; i < mapWidth; i++)
	// {
	// 	for (int j = 0 ; j < mapHeight; j++)
	// 	{
	// 		info.worldMap[i][j] = world[i][j];
	// 	}
	// }
	init(&info);
	open_file_with_validate(argv[1], &info);
	if (!set_texture(&info.window.texture))
		return (0);
	load_texture(&info);
	
	mlx_loop_hook(info.window.mlx, &main_loop, &info);
	mlx_hook(info.window.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.window.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);
	mlx_hook(info.window.win, BUTTON_CLOSE, 0, &exit_button_close, NULL);
	mlx_loop(info.window.mlx);
}