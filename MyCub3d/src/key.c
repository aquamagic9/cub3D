#include "../includes/cub3d.h"

int	key_release(int key, t_key *key_state)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		key_state->key_w = 0;
	else if (key == K_A)
		key_state->key_a = 0;
	else if (key == K_S)
		key_state->key_s = 0;
	else if (key == K_D)
		key_state->key_d = 0;
	else if (key == K_LEFT)
		key_state->key_left = 0;
	else if (key == K_RIGHT)
		key_state->key_right = 0;
	return (0);
}

void	key_update(t_key *key, t_move *move, int **worldMap)
{
	// if (key->key_w)
	// {
	// 	if (!worldMap[(int)(move->pos.vx + move->dir.vx * move->moveSpeed)][(int)(move->pos.vy)])
	// 		move->pos.vx += move->dir.vx * move->moveSpeed;
	// 	if (!worldMap[(int)(move->pos.vx)][(int)(move->pos.vy + move->dir.vy * move->moveSpeed)])
	// 		move->pos.vy += move->dir.vy * move->moveSpeed;
	// }
	// if (key->key_s)
	// {
	// 	if (!worldMap[(int)(move->pos.vx - move->dir.vx * move->moveSpeed)][(int)(move->pos.vy)])
	// 		move->pos.vx -= move->dir.vx * move->moveSpeed;
	// 	if (!worldMap[(int)(move->pos.vx)][(int)(move->pos.vy - move->dir.vy * move->moveSpeed)])
	// 		move->pos.vy -= move->dir.vy * move->moveSpeed;
	// }
	// if (key->key_a)
	// {
	// 	if (!worldMap[(int)(move->pos.vx - move->plane.vx * move->moveSpeed)][(int)(move->pos.vy)])
	// 		move->pos.vx -= move->plane.vx * move->moveSpeed;
	// 	if (!worldMap[(int)(move->pos.vx)][(int)(move->pos.vy - move->plane.vy * move->moveSpeed)])
	// 		move->pos.vy -= move->plane.vy * move->moveSpeed;
	// }
	// if (key->key_d)
	// {
	// 	if (!worldMap[(int)(move->pos.vx + move->plane.vx * move->moveSpeed)][(int)(move->pos.vy)])
	// 		move->pos.vx += move->plane.vx * move->moveSpeed;
	// 	if (!worldMap[(int)(move->pos.vx)][(int)(move->pos.vy + move->plane.vy * move->moveSpeed)])
	// 		move->pos.vy += move->plane.vy * move->moveSpeed;
	// }
	if (key->key_w)
	{
		if (!worldMap[(int)(move->pos.vy)][(int)(move->pos.vx + move->dir.vx * move->moveSpeed)])
			move->pos.vx += move->dir.vx * move->moveSpeed;
		if (!worldMap[(int)(move->pos.vy + move->dir.vy * move->moveSpeed)][(int)(move->pos.vx)])
			move->pos.vy += move->dir.vy * move->moveSpeed;
	}
	if (key->key_s)
	{
		if (!worldMap[(int)(move->pos.vy)][(int)(move->pos.vx - move->dir.vx * move->moveSpeed)])
			move->pos.vx -= move->dir.vx * move->moveSpeed;
		if (!worldMap[(int)(move->pos.vy - move->dir.vy * move->moveSpeed)][(int)(move->pos.vx)])
			move->pos.vy -= move->dir.vy * move->moveSpeed;
	}
	if (key->key_a)
	{
		if (!worldMap[(int)(move->pos.vy)][(int)(move->pos.vx - move->plane.vx * move->moveSpeed)])
			move->pos.vx -= move->plane.vx * move->moveSpeed;
		if (!worldMap[(int)(move->pos.vy - move->plane.vy * move->moveSpeed)][(int)(move->pos.vx)])
			move->pos.vy -= move->plane.vy * move->moveSpeed;
	}
	if (key->key_d)
	{
		if (!worldMap[(int)(move->pos.vy)][(int)(move->pos.vx + move->plane.vx * move->moveSpeed)])
			move->pos.vx += move->plane.vx * move->moveSpeed;
		if (!worldMap[(int)(move->pos.vy + move->plane.vy * move->moveSpeed)][(int)(move->pos.vx)])
			move->pos.vy += move->plane.vy * move->moveSpeed;
	}

	if (key->key_left)
		rotate_my_view(move, -move->rotSpeed);
	if (key->key_right)
		rotate_my_view(move, move->rotSpeed);
	if (key->key_esc)
		exit(0);
}

int	key_press(int key, t_key *key_state)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		key_state->key_w = 1;
	else if (key == K_A)
		key_state->key_a = 1;
	else if (key == K_S)
		key_state->key_s = 1;
	else if (key == K_D)
		key_state->key_d = 1;
	else if (key == K_LEFT)
		key_state->key_left = 1;
	else if (key == K_RIGHT)
		key_state->key_right = 1;
	return (0);
}
