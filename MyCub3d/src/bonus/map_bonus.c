/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:35 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:01:08 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

static int	put_map_data(char *line, t_info *info)
{
	int			width_index;
	static int	height_index;

	width_index = 0;
	if (!is_valid_map_line(line))
		exit_with_error("Invalid Map Token");
	if (height_index == info->map_height)
		return (0);
	while (line[width_index])
	{
		if (line[width_index] == '1')
			info->world_map[height_index][width_index] = M_WALL;
		else if (line[width_index] == ' ')
			info->world_map[height_index][width_index] = M_VOID;
		else if (ft_strchr("NSWE", line[width_index]))
		{
			if (info->move.pos.vx != -1.0)
				exit_with_error("duplicate player");
			set_player_pos_direction(&info->move, line[width_index], \
				width_index, height_index);
		}
		width_index++;
	}
	height_index++;
	return (0);
}

int	record_map_data(char *line, t_info *info)
{
	int	new_width;

	new_width = ft_strlen(line);
	if (new_width > info->map_width)
		info->map_width = new_width;
	info->map_height++;
	return (0);
}

void	malloc_map(t_info *info)
{
	int	i;

	i = 0;
	info->world_map = (int **)malloc(sizeof(int *) * info->map_height);
	if (!info->world_map)
		exit_with_error("Map Malloc Error");
	while (i < info->map_height)
	{
		info->world_map[i] = (int *)malloc(sizeof(int) * info->map_width);
		if (!info->world_map[i])
			exit_with_error("Map Malloc Error");
		ft_memset(info->world_map[i], M_BLANK, sizeof(int) * info->map_width);
		i++;
	}
}

int	save_map(char *file_path, t_info *info)
{
	char	*line;
	int		fd;
	int		i;

	fd = ft_open(file_path);
	jump(fd, info);
	line = get_next_line_without_nl(fd);
	if (line == NULL)
		exit_with_error("Check the file type");
	while (line)
	{
		i = 0;
		while (ft_isspace(line[i]))
		i++;
		if (ft_isdigit(line[i]) || (line[i] == '\0' && info->map_height > 0))
			put_map_data(line, info);
		free(line);
		line = get_next_line_without_nl(fd);
	}
	free(line);
	return (0);
}
