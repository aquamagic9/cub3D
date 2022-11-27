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