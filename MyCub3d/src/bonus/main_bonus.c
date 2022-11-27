/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:33 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:15:07 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

int	main_loop(t_info *info)
{
	draw_background(info->window.buf, \
		switch_color(info->color_set[Z_FLOOR]), \
			switch_color(info->color_set[Z_CEILING]));
	ray_casting(&info->move, &info->window, info->world_map);
	draw(&info->window);
	key_update(&info->key, &info->move, info->world_map);
	return (0);
}

int	exit_button_close(void)
{
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc != 2)
		exit_with_error("Invalid argc");
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
