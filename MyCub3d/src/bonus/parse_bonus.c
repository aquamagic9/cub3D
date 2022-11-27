/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:38 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 01:16:02 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

int	type_router(char *type, char *value, t_info *info)
{
	if (info->map_height > 0)
		exit_with_error("Invalid config position");
	if (ft_strncmp(type, "NO", 3) == 0)
		return (save_wall_texture(value, D_NORTH, info));
	else if (ft_strncmp(type, "SO", 3) == 0)
		return (save_wall_texture(value, D_SOUTH, info));
	else if (ft_strncmp(type, "WE", 3) == 0)
		return (save_wall_texture(value, D_WEST, info));
	else if (ft_strncmp(type, "EA", 3) == 0)
		return (save_wall_texture(value, D_EAST, info));
	else if (ft_strncmp(type, "F", 2) == 0)
		return (save_ceil_floor_color(value, Z_FLOOR, info));
	else if (ft_strncmp(type, "C", 2) == 0)
		return (save_ceil_floor_color(value, Z_CEILING, info));
	else
		return (T_ERROR);
}

int	check_contents(char *line, t_info *info)
{
	char		**data_set;
	static int	index;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (ft_isspace(line[i]))
	i++;
	if (ft_isdigit(line[i]) || (line[i] == '\0' && info->map_height > 0))
	{
		if (info->map_start_index == 0)
			info->map_start_index = index;
		return (record_map_data(line, info));
	}
	index++;
	if (line[i] == '\0')
		return (0);
	data_set = ft_split(line, ' ');
	while (data_set[j] != NULL)
	j++;
	if (j != 2)
		exit_with_error("Invalid config");
	type_router(data_set[0], data_set[1], info);
	return (free_split(data_set));
}

int	recovery(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->map_height)
	{
		j = 0;
		while (j < info->map_width)
		{
			if (info->world_map[i][j] == 3)
			info->world_map[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

void	open_file_with_validate(char *file_path, t_info *info)
{
	int		fd;
	char	*line;

	file_extention_validator(file_path);
	fd = ft_open(file_path);
	line = get_next_line_without_nl(fd);
	if (line == NULL)
		exit_with_error("Check the file type");
	while (line)
	{
		check_contents(line, info);
		free(line);
		line = get_next_line_without_nl(fd);
	}
	free(line);
	ft_close(fd);
	validation_config(info);
	malloc_map(info);
	save_map(file_path, info);
	validation_map(info);
}
