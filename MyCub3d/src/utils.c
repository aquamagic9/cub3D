/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:56:24 by junseo            #+#    #+#             */
/*   Updated: 2022/11/27 21:56:24 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_next_line_without_nl(int fd)
{
	char	*result;
	int		len;

	result = get_next_line(fd);
	if (!result)
		return (NULL);
	len = ft_strlen(result);
	if (result[len - 1] == '\n')
	{
		result[ft_strlen(result) - 1] = '\0';
	}
	return (result);
}

int	ft_close(int fd)
{
	if (close(fd) == -1)
		exit_with_error("During close map file");
	return (0);
}

int	ft_open(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		exit_with_error("Can't open file");
	return (fd);
}

int	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i] != NULL)
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
	return (0);
}

int	jump(int fd, t_info *info)
{
	char	*temp;
	int		i;

	i = 0;
	temp = get_next_line_without_nl(fd);
	while (i < info->map_start_index - 1)
	{
		free(temp);
		temp = get_next_line_without_nl(fd);
		i++;
	}
	free(temp);
	return (0);
}
