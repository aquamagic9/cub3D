#include "../includes/cub3d.h"

int	key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!info->worldMap[(int)(info->pos.vx + info->dir.vx * info->moveSpeed)][(int)(info->pos.vy)])
			info->pos.vx += info->dir.vx * info->moveSpeed;
		if (!info->worldMap[(int)(info->pos.vx)][(int)(info->pos.vy + info->dir.vy * info->moveSpeed)])
			info->pos.vy += info->dir.vy * info->moveSpeed;
	}
	if (info->key_s)
	{
		if (!info->worldMap[(int)(info->pos.vx - info->dir.vx * info->moveSpeed)][(int)(info->pos.vy)])
			info->pos.vx -= info->dir.vx * info->moveSpeed;
		if (!info->worldMap[(int)(info->pos.vx)][(int)(info->pos.vy - info->dir.vy * info->moveSpeed)])
			info->pos.vy -= info->dir.vy * info->moveSpeed;
	}
	if (info->key_d)
		rotate_my_view(info, -info->rotSpeed);
	if (info->key_a)
		rotate_my_view(info, info->rotSpeed);
	if (info->key_esc)
		exit(0);
}

int	key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}
