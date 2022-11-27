/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:56:26 by junseo            #+#    #+#             */
/*   Updated: 2022/11/27 21:56:26 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr("01NSEW ", line[i]) == NULL)
			return (0);
		i++;
	}
	return (1);
}

static int	flood_fill(int x, int y, t_info *info)
{
	int			i;
	const int	direction[5] = {1, 0, -1, 0, 1};

	i = 0;
	if (x < 0 || x >= info->map_width || y < 0 || y >= info->map_height)
		exit_with_error("not protect wall?");
	if (info->world_map[y][x] == 2)
		exit_with_error("found void");
	if (info->world_map[y][x] == 1 || info->world_map[y][x] == 3)
		return (1);
	info->world_map[y][x] = 3;
	while (i < 4)
	{
		flood_fill(x + direction[i], y + direction[i + 1], info);
		i++;
	}
	return (1);
}

void	file_extention_validator(char *file_name)
{
	if (!file_name || ft_strncmp(file_name + ft_strlen(file_name) - 4, \
	".cub", 4))
		exit_with_error("Invalid file name");
}

int	validation_map(t_info *info)
{
	if (info->move.pos.vx == -1 || info->move.pos.vy == -1)
		exit_with_error("No Player");
	flood_fill(info->move.pos.vx, info->move.pos.vy, info);
	recovery(info);
	return (0);
}

int	validation_config(t_info *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (info->texture_file == NULL)
			exit_with_error("Texture is empty");
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (info->color_set[i].r + info->color_set[i].g + \
		info->color_set[i].b == -3)
			exit_with_error("Color is empty");
	i++;
	}
	return (0);
}
