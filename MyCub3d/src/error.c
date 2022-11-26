#include "../includes/cub3d.h"

void  exit_with_error(char *str)
{
  printf("Error\n");
  if (str)
    printf("%s\n", str);
  exit(1);
}