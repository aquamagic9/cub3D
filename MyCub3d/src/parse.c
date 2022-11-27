#include "../includes/cub3d.h"

void  free_split(char **split)
{
  int i;

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
}

int	save_wall_texture(char *line, enum e_direction direction, t_info *info)
{
	 // 2-5-1
	if (info->texture_file[direction] != NULL)
		exit_with_error("duplicated texture file");
	info->texture_file[direction] = ft_substr(line, 0, ft_strlen(line));
	return (0);
}

int	save_ceil_floor_color(char *value, enum e_zAxis z, t_info *info)
{
	char	**color_set;
	int		i;
	int		j;
	int		color[3];

	i = 0;
	color_set = ft_split(value, ','); // 2-5-1
	while (color_set[i] != NULL)
		i++;
	if (i != 3) // 2-5-1
		exit_with_error("Invalid color count");
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (color_set[i][j])
		{
			if (!ft_isdigit(color_set[i][j])) //2-5-2
				exit_with_error("Invalid color value! is not numeric TT");
			j++;
		}
		color[i] = ft_atoi(color_set[i]);
		if (color[i] < 0 || color[i] > 255) // 2-5-3
			exit_with_error("Invalid color range");
		i++;
	}
	if ((info->color_set[z].r + info->color_set[z].g + info->color_set[z].b) != -3) // 2-5-4
    exit_with_error("duplicated color info");
  set_color(&info->color_set[z], color[0], color[1], color[2]);
	free_split(color_set);
  return (0);
}

int record_map_data(char *line, t_info *info)
{
  int new_width;

  new_width = ft_strlen(line);
  if (new_width > info->map_width)
    info->map_width = new_width; // 3-1-2
  info->map_height++;
  return (0);
}

int type_router(char *type, char *value, t_info *info)
{
  if (info->map_height > 0)
    exit_with_error("Invalid config position found between map"); // 2-5
  if (ft_strncmp(type, "NO", 3) == 0)
    return save_wall_texture(value, D_NORTH, info);
  else if (ft_strncmp(type, "SO", 3) == 0)
    return save_wall_texture(value, D_SOUTH, info);
  else if (ft_strncmp(type, "WE", 3) == 0)
    return save_wall_texture(value, D_WEST, info);
  else if (ft_strncmp(type, "EA", 3) == 0)
    return save_wall_texture(value, D_EAST, info);
  else if (ft_strncmp(type, "F", 2) == 0)
    return (save_ceil_floor_color(value, Z_FLOOR, info));
  else if (ft_strncmp(type, "C", 2) == 0)
    return (save_ceil_floor_color(value, Z_CEILING, info));
  else
    return (T_ERROR);
}

int  check_contents(char *line, t_info *info)
{
  static  int index;
  char        **data_set;
  int         i;
  int         j;

  i = 0;
  j = 0;
  while (ft_isspace(line[i])) // 2-2
    i++;
  if (ft_isdigit(line[i]) || (line[i] == '\0' && info->map_height > 0))
  {
    if (info->map_start_index == 0) // 3-1-1
      info->map_start_index = index;
    return (record_map_data(line, info));
  } // 2-2
  index++;
  if (line[i] == '\0')
    return (0);
  data_set = ft_split(line, ' '); // 2-3
  while (data_set[j] != NULL)
    j++;
  if (j != 2) // 2-4
    exit_with_error("Invalid config");
  type_router(data_set[0], data_set[1], info);
  free_split(data_set);
  return (0);
}

void  file_extention_validator(char *file_name)
{
  if (!file_name || ft_strncmp(file_name + ft_strlen(file_name) - 4, ".cub", 4))
    exit_with_error("Invalid file name");
}

int   ft_open(char *str)
{
  int fd;
  fd = open(str, O_RDONLY);
  if (fd == -1)
      exit_with_error("Can't open file");
  return (fd);
}

int   ft_close(int fd)
{
  int result;
  
  result = close(fd);
  if (result == -1)
    exit_with_error("During close map file");
  return (result);
}

static  int is_valid_map_line(char *line)
{
  int i;
  i = 0;
  while (line[i])
  {
    if (ft_strchr("01NSEW ", line[i]) == NULL)
      return (0);
    i++;
  }
  return (1);
}

void  malloc_map(t_info *info)
{
  int i;

  i = 0;
  info->worldMap = (int **)malloc(sizeof(int *) * info->map_height); // 4-4
  if (!info->worldMap)
    exit_with_error("Map Malloc Error");
  while (i < info->map_height)
  {
    info->worldMap[i] = (int *)malloc(sizeof(int) * info->map_width);
    if (!info->worldMap[i])
      exit_with_error("Map Malloc Error");
    ft_memset(info->worldMap[i], M_BLANK, sizeof(int) * info->map_width);
    i++;
  }
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

int	set_player_direction(t_move* move, char dir)
{
  move->dir.vx = 0;
	move->dir.vy = -1;
	if (dir == 'N')
	{
    ;
	}
	else if (dir == 'S')
	{
		rotate_my_view(move, PI);
	}
	else if (dir == 'W')
	{
		rotate_my_view(move, -PI/2);
	}
	else if (dir == 'E')
	{
		rotate_my_view(move, PI/2);
	}
	return (0);
}

int	put_map_data(char *line, t_info *info)
{
	int			width_index;
	static int	height_index;

	width_index = 0;
	if (!is_valid_map_line(line)) // 3-2-1
		exit_with_error("Invalid Map Token");
	if (height_index == info->map_height)
		return (0);
	while (line[width_index])
	{
		if (line[width_index] == '1')
		info->worldMap[height_index][width_index] = M_WALL;
		else if (line[width_index] == ' ')
		info->worldMap[height_index][width_index] = M_VOID;
		else if (ft_strchr("NSWE", line[width_index]))
		{
			if (info->move.pos.vx != -1.0) // 3-2-2
				exit_with_error("duplicate player");
			info->move.pos.vx = width_index + 0.5f;
			info->move.pos.vy = height_index + 0.5f;
			set_player_direction(&info->move, line[width_index]);
		}
		width_index++;
	}
	height_index++;
	return (0);
}

int	save_map(char *file_path, t_info *info)
{
	char	*line;
	int		fd;
	int		i;

	fd = ft_open(file_path);
	jump(fd, info); // 3-1-3
	line = get_next_line_without_nl(fd);
	if (line == NULL) // 1-3
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

int	flood_fill(int x, int y, t_info *info)
{
	int			i;
	const int	direction[5] = {1, 0, -1, 0, 1};

	i = 0;
	if (x < 0 || x >= info->map_width || y < 0 || y >= info->map_height)
		exit_with_error("not protect wall?");
	if (info->worldMap[y][x] == 2)
		exit_with_error("found void");
	if (info->worldMap[y][x] == 1 || info->worldMap[y][x] == 3)
		return (1);
	info->worldMap[y][x] = 3;
	while (i < 4)
	{
		flood_fill(x + direction[i], y + direction[i + 1], info);
		i++;
	}
	return (1);
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
			if (info->worldMap[i][j] == 3)
			info->worldMap[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int	validation_map(t_info *info)
{
	if (info->move.pos.vx == -1 || info->move.pos.vy == -1)
		exit_with_error("No Player");
	flood_fill(info->move.pos.vx, info->move.pos.vy, info); // 3-2-3
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

void	print_info(t_info *info)
{
	printf("\nwidth:%d\nheight:%d\n", info->map_width, info->map_height);
	printf("\ncelling R:%d\ncelling G:%d\ncelling B:%d\n", info->color_set[Z_CEILING].r, info->color_set[Z_CEILING].g, info->color_set[Z_CEILING].b);
	printf("\nfloor R:%d\nfloor G:%d\nfloor B:%d\n\n", info->color_set[Z_FLOOR].r, info->color_set[Z_FLOOR].g, info->color_set[Z_FLOOR].b);

	printf("NO Texture:%s\n", info->texture_file[T_NO]);
	printf("SO Texture:%s\n", info->texture_file[T_SO]);
	printf("WE Texture:%s\n", info->texture_file[T_WE]);
	printf("EA Texture:%s\n", info->texture_file[T_EA]);
	printf("\n");

	printf("Player Position x:%f y:%f", info->move.pos.vx, info->move.pos.vy);
	printf("EA Texture:%s\n", info->texture_file[T_EA]);


	for (int i = 0; i < info->map_height; i+=1)
	{
		for (int j = 0; j < info->map_width; j+=1)
		{
			printf("%d", info->worldMap[i][j]);
		}
		printf("\n");
	}
}

void  open_file_with_validate(char *file_path, t_info *info)
{
	int		fd;
	char	*line;

	file_extention_validator(file_path); // 1-1
	fd = ft_open(file_path); // 1-2
	line = get_next_line_without_nl(fd); 
	if (line == NULL) // 1-3
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
	print_info(info);
}

/*
  1. 플레이어 위치 확인 후 저장 (포지션, 방향)
  2. 맵 저장 (가로, 세로)
  3. 텍스쳐 path 저장
  4. 바닥 천장 색상 저장 및 적용
  5. 리커버리

  TODO:
  1. 텍스쳐 오픈
  2. 동서남북 적용
*/
