#include "../includes/cub3d.h"

int save_wall_texture(char *line, enum e_direction direction, t_info *info)
{
  if (info->texture_file[direction] != NULL)
    exit_with_error("Error: duplicated texture file");
  info->texture_file[direction] = ft_substr(line, 3, ft_strlen(line));
  return (0);
}

int save_ceil_floor_color(char *line, enum e_zAxis z, t_info *info)
{
	int	color[3];
	int	i;
	int	count;

	i = 2;
	count = 0;
	

	char **color_set;
	
	color_set = ft_split(line + 2, ',');

	while (color_set[count])
	{
		color[count] = ft_atoi(color_set[count]);
		if (color[count] < 0 || color[count] > 255)
			exit_with_error("Invalid Color Range");
	}


	while (line[i] && count <= 2)
	{
		while (ft_isspace(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			color[count] = ft_atoi(line + i);
		if (color[count] < 0 || color[count] > 255)
			exit_with_error("Invalid Color Range");
		while (line[i] && (ft_isdigit(line[i]) || line[i] == '\n'))
			i++;
		if (line[i] && line[i] != ',')
			exit_with_error("Invalid Color Type");
		if (line[i] && line[i] == ',')
			count++;
	}
	if (count != 2)
		exit_with_error("Color");
	printf("1: %d\n2: %d\n3: %d\n", color[0], color[1], color[2]); // TODO: CHECK
	return (1);
}

int  check_contents(char *line, t_info *info)
{
  if (ft_strncmp(line, "NO ", 3) == 0)
    return save_wall_texture(line, D_NORTH, info);
  else if (ft_strncmp(line, "SO ", 3) == 0)
    return save_wall_texture(line, D_SOUTH, info);
  else if (ft_strncmp(line, "WE ", 3) == 0)
    return save_wall_texture(line, D_WEST, info);
  else if (ft_strncmp(line, "EA ", 3) == 0)
    return save_wall_texture(line, D_EAST, info);
  else if (ft_strncmp(line, "F ", 2) == 0)
    return (save_ceil_floor_color(line, Z_FLOOR, info));
  else if (ft_strncmp(line, "C ", 2) == 0)
    return (save_ceil_floor_color(line, Z_CEILING, info));
  else if (ft_strchr("012NSEW ", line[0]))
    return (T_MAP);
  else if (line[0] == '\n')
    return (T_EMPTY);
  else
    return (T_ERROR);
}

void  is_valid_file_name(char *file_name)
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

static  int is_valid_map_line(char *line)
{
  int i;
  i = 0;
  while (line[i])
  {
    if (ft_strchr("012NSEW ", line[i]) == NULL)
      return (0);
  }
  return (1);
}

void  open_file_with_validate(char *file_path, t_info *info)
{
  int fd;
  char  *line;
  int   ret;
  enum e_texture   parse_type;

  is_valid_file_name(file_path);
  fd = ft_open(file_path);
  line = get_next_line(fd);
  while (line){
	  check_contents(line, info);
	  free(line);
  }
}
/*
  위와 아래는 다른 색상으로 처리
  맵 유형
  - 0 : 빈공간
  - 1 : 벽
  - N | S | W | E : 플레이어의 시작 위치인데 이때 플레이어의 방향을 나타냄
  맵은 정사각형이 아닐 수 있다!
  1. 확장자 예외처리 (.cub)
  2. 맵 유효성 검사
    -a: 맵의 가장자리가 1로 둘러쌓여있는지
    -b: 플레이어가 맵 안에 있는지 (1명만)
    -c: 플레이어의 방향이 N | S | W | E 인지
    -d: 맵 중간에 빈 공간이 있는지
    -e: 다른 문자가 있는지
  3. 플레이어 위치 저장
  .cub 파일 - Identifier
존재하지 않는 파일 이름 (ex: none.cub)
존재하지 않는 텍스처 파일 이름 (ex: blue.xpm)
잘못된 RGB 값 입력 (0~255 범위 밖)
RGB 값이 들어갈 자리에 숫자를 넣지 않는 경우
정의되지 않은 identifier 문자가 있는 경우 (EA, WE, SO, NO, F, C 이외 모든 문자)
맵 컨텐츠와 identifier 순서가 뒤바뀐 경우
유효하지 않은 맵 검사 (cub3D_map_tester 테스터 사용)
.cub 파일 - Map contents
맵 내부 구성에 빈 줄 또는 공백
플레이어가 맵 바깥에 있는 경우
플레이어 수가 1명이 아닌 경우
맵 내부 구성에서 서브젝트에 정의되지 않은 문자가 나온 경우(0, 1, E, W, S, N, ' ' 제외한 모든 문자)
*/