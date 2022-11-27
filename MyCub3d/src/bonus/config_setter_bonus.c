/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_setter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:15 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:00:42 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

int	save_wall_texture(char *line, enum e_direction direction, t_info *info)
{
	if (info->texture_file[direction] != NULL)
		exit_with_error("duplicated texture file");
	info->texture_file[direction] = ft_substr(line, 0, ft_strlen(line));
	return (0);
}

static void	validation_color_value(char *color, int *value)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			exit_with_error("Invalid color value! is not numeric TT");
		i++;
	}
	*value = ft_atoi(color);
	if ((*value) < 0 || (*value) > 255)
		exit_with_error("Invalid color range");
	return ;
}

int	save_ceil_floor_color(char *value, enum e_zAxis z, t_info *info)
{
	char	**color_set;
	int		i;
	int		color[3];

	i = 0;
	color_set = ft_split(value, ',');
	while (color_set[i] != NULL)
		i++;
	if (i != 3)
		exit_with_error("Invalid color count");
	i = 0;
	while (i < 3)
	{
		validation_color_value(color_set[i], &color[i]);
		i++;
	}
	if ((info->color_set[z].r + info->color_set[z].g + info->color_set[z].b) \
	!= -3)
		exit_with_error("duplicated color info");
	set_color(&info->color_set[z], color[0], color[1], color[2]);
	free_split(color_set);
	return (0);
}

int	set_player_pos_direction(t_move *move, char dir, \
	int width_index, int height_index)
{
	move->pos.vx = width_index + 0.5f;
	move->pos.vy = height_index + 0.5f;
	if (dir == 'N')
		;
	else if (dir == 'S')
		rotate_my_view(move, PI);
	else if (dir == 'W')
		rotate_my_view(move, -PI / 2);
	else if (dir == 'E')
		rotate_my_view(move, PI / 2);
	else
		exit_with_error("Invalid Direction!");
	return (0);
}
