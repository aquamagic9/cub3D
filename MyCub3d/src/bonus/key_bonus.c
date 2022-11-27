/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:27 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:01:08 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

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

void	key_move(int **world_map, t_vec *pos, t_vec dir, double speed)
{
	if (!world_map[(int)(pos->vy)][(int)(pos->vx + dir.vx * speed)])
		pos->vx += dir.vx * speed;
	if (!world_map[(int)(pos->vy + dir.vy * speed)][(int)(pos->vx)])
		pos->vy += dir.vy * speed;
}

void	key_update(t_key *key, t_move *move, int **world_map)
{
	if (key->key_w)
		key_move(world_map, &move->pos, move->dir, move->move_speed);
	if (key->key_s)
		key_move(world_map, &move->pos, \
			multiple_vector(-1, move->dir), move->move_speed);
	if (key->key_a)
		key_move(world_map, &move->pos, \
			multiple_vector(-1, move->plane), move->move_speed);
	if (key->key_d)
		key_move(world_map, &move->pos, move->plane, move->move_speed);
	if (key->key_left)
		rotate_my_view(move, -move->rot_speed);
	if (key->key_right)
		rotate_my_view(move, move->rot_speed);
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
