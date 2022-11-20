
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../mlx/mlx.h"
#include "../includes/cub3d.h"



void rotate(double *x, double *y, double angle)
{
	double old;

	old = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = old * sin(angle) + *y * cos(angle);
}

void rotateMyView(t_info *info, double angle)
{
	rotate(&info->dir.vx, &info->dir.vy, angle);
	rotate(&info->plane.vx, &info->plane.vy, angle);
}

t_vec plusVector(t_vec a, t_vec b)
{
	t_vec result;

	result.vx = a.vx + b.vx;
	result.vy = a.vy + b.vy;
	return result;
}

t_vec minusVector(t_vec a, t_vec b)
{
	t_vec result;

	result.vx = a.vx - b.vx;
	result.vy = a.vy - b.vy;
	return result;
}

t_vec multipleVector(double k, t_vec a)
{
	t_vec result;

	result.vx = k * a.vx;
	result.vy = k * a.vy;

	return result;
}

void init(t_info *info)
{
	info->mlx = mlx_init();
	info->pos.vx = 22.0;
	info->pos.vy = 11.5;
	info->dir.vx = -1.0;
	info->dir.vy = 0.0;
	info->plane.vx = 0.0;
	info->plane.vy = 0.66;
	info->key_a = 0;
	info->key_w = 0;
	info->key_s = 0;
	info->key_d = 0;
	info->key_esc = 0;
	info->moveSpeed = 0.05;
	info->rotSpeed = 0.05;
	info->win = mlx_new_window(info->mlx, width, height, "mlx");
	info->img.img = mlx_new_image(info->mlx, width, height);
	info->img.data = (int *)mlx_get_data_addr(info->img.img, &info->img.bpp, &info->img.size_l, &info->img.endian);
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			info->buf[i][j] = 0;
}

int setTexture(int ***texture)
{
	int size;

	size = 11;
	if (!(*texture = (int **)malloc(sizeof(int *) * size)))
		return (-1);
	for (int i = 0; i < size; i++)
		if (!((*texture)[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < texHeight * texWidth; j++)
			(*texture)[i][j] = 0;
	return (1);
}





int	worldMap[mapWidth][mapHeight] =
									{
										{8,8,8,8,8,8,8,8,8,8,8,4,4,6,4,4,6,4,6,4,4,4,6,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6},
										{8,0,3,3,0,0,0,0,0,8,8,4,0,0,0,0,0,0,0,0,0,0,0,4},
										{8,0,0,0,0,0,0,0,0,0,8,4,0,0,0,0,0,6,6,6,0,6,4,6},
										{8,8,8,8,0,8,8,8,8,8,8,4,4,4,4,4,4,6,0,0,0,0,0,6},
										{7,7,7,7,0,7,7,7,7,0,8,0,8,0,8,0,8,4,0,4,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,0,0,0,0,0,6},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,0,0,0,0,4},
										{7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,6,0,6,0,6,0,6},
										{7,7,0,0,0,0,0,0,7,8,0,8,0,8,0,8,8,6,4,6,0,6,6,6},
										{7,7,7,7,0,7,7,7,7,8,8,4,0,6,8,4,8,3,3,3,0,3,3,3},
										{2,2,2,2,0,2,2,2,2,4,6,4,0,0,6,0,6,3,0,0,0,0,0,3},
										{2,2,0,0,0,0,0,2,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{2,0,0,0,0,0,0,0,2,4,0,0,0,0,0,0,4,3,0,0,0,0,0,3},
										{1,0,0,0,0,0,0,0,1,4,4,4,4,4,6,0,6,3,3,0,0,0,3,3},
										{2,0,0,0,0,0,0,0,2,2,2,1,2,2,2,6,6,0,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
										{2,0,0,0,0,0,0,0,2,0,0,0,0,0,2,5,0,5,0,5,0,5,0,5},
										{2,2,0,0,0,0,0,2,2,2,0,0,0,2,2,0,5,0,5,0,0,0,5,5},
										{2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,5,5,5,5,5,5,5,5,5}
									};

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			info->img.data[y * width + x] = info->buf[y][x];
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	for(int y = 0; y < height; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		
		// float rayDirX0 = info->dirX - info->planeX;
		// float rayDirY0 = info->dirY - info->planeY;
		// float rayDirX1 = info->dirX + info->planeX;
		// float rayDirY1 = info->dirY + info->planeY;

		t_vec rayDir0 = plusVector(info->dir, info->plane);
		t_vec rayDir1 = minusVector(info->dir, info->plane);

		// Current y position compared to the center of the screen (the horizon)
		int p = y - height / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		
		// float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / width;
		// float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / width;

		t_vec floorStep = multipleVector(rowDistance / (float)width, minusVector(rayDir1, rayDir0));

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		// float floorX = info->posX + rowDistance * rayDirX0;
		// float floorY = info->posY + rowDistance * rayDirY0;
		t_vec floor = plusVector(info->pos , multipleVector(rowDistance, rayDir0));

		for(int x = 0; x < width; x++)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floor.vx);
			int cellY = (int)(floor.vy);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floor.vx - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floor.vy - cellY)) & (texHeight - 1);

			// floorX += floorStepX;
			// floorY += floorStepY;
			floor = plusVector(floor, floorStep);

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			// floor
			color = info->texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[y][x] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[height - y - 1][x] = color;
		}
	}
	//WALL CASTING
	for(int x = 0; x < width; x++)
	{
		double cameraX = 2 * x / (double)width - 1;
		// double rayDirX = info->dirX + info->planeX * cameraX;
		// double rayDirY = info->dirY + info->planeY * cameraX;
		t_vec rayDir = plusVector(info->dir, multipleVector(cameraX, info->plane));
		
		int mapX = (int)info->pos.vx;
		int mapY = (int)info->pos.vy;

		//length of ray from current position to next x or y-side
		// double sideDistX;
		// double sideDistY;
		t_vec sideDist;
		
		 //length of ray from one x or y-side to next x or y-side
		// double deltaDistX = fabs(1 / rayDirX);
		// double deltaDistY = fabs(1 / rayDirY);
		t_vec deltaDist;
		deltaDist.vx = fabs(1 / rayDir.vx);
		deltaDist.vy = fabs(1 / rayDir.vy);

		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDir.vx < 0)
		{
			stepX = -1;
			sideDist.vx = (info->pos.vx - mapX) * deltaDist.vx;
		}
		else
		{
			stepX = 1;
			sideDist.vx = (mapX + 1.0 - info->pos.vx) * deltaDist.vx;
		}
		if (rayDir.vy < 0)
		{
			stepY = -1;
			sideDist.vy = (info->pos.vy - mapY) * deltaDist.vy;
		}
		else
		{
			stepY = 1;
			sideDist.vy = (mapY + 1.0 - info->pos.vy) * deltaDist.vy;
		}

		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDist.vx < sideDist.vy)
			{
				sideDist.vx += deltaDist.vx;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDist.vy += deltaDist.vy;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - info->pos.vx + (1 - stepX) / 2) / rayDir.vx;
		else
			perpWallDist = (mapY - info->pos.vy + (1 - stepY) / 2) / rayDir.vy;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		if(drawEnd >= height)
			drawEnd = height - 1;

		// texturing calculations
		int texNum = worldMap[mapX][mapY] - 1;

		// calculate value of wallX
		double wallX;
		if (side == 0)
			wallX = info->pos.vy + perpWallDist * rayDir.vy;
		else
			wallX = info->pos.vx + perpWallDist * rayDir.vx;
		wallX -= floor(wallX);

		// x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDir.vx > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDir.vy < 0)
			texX = texWidth - texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		double step = 1.0 * texHeight / lineHeight;

		// Starting texture coordinate
		double texPos = (drawStart - height / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;

			int color = info->texture[texNum][texHeight * texY + texX];

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;

			info->buf[y][x] = color;
		}

		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && rayDir.vx > 0)
		{
			floorXWall = mapX;
			floorYWall = mapY + wallX;
		}
		else if(side == 0 && rayDir.vx < 0)
		{
			floorXWall = mapX + 1.0;
			floorYWall = mapY + wallX;
		}
		else if(side == 1 && rayDir.vy > 0)
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY;
		}
		else
		{
			floorXWall = mapX + wallX;
			floorYWall = mapY + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd + 1; y < height; y++)
		{
			currentDist = height / (2.0 * y - height); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * info->pos.vx;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * info->pos.vy;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * texWidth) % texWidth;
			floorTexY = (int)(currentFloorY * texHeight) % texHeight;

			int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
			int floorTexture;
			if(checkerBoardPattern == 0) floorTexture = 3;
			else floorTexture = 4;

			//floor
			info->buf[y][x] = (info->texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			info->buf[height - y][x] = info->texture[6][texWidth * floorTexY + floorTexX];
		}
	}
}

int		key_press(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 1;
	else if (key == K_A)
		info->key_a = 1;
	else if (key == K_S)
		info->key_s = 1;
	else if (key == K_D)
		info->key_d = 1;
	return (0);
}

void	key_update(t_info *info)
{
	if (info->key_w)
	{
		if (!worldMap[(int)(info->pos.vx + info->dir.vx * info->moveSpeed)][(int)(info->pos.vy)])
			info->pos.vx += info->dir.vx * info->moveSpeed;
		if (!worldMap[(int)(info->pos.vx)][(int)(info->pos.vy + info->dir.vy * info->moveSpeed)])
			info->pos.vy += info->dir.vy * info->moveSpeed;
	}
	if (info->key_s)
	{
		if (!worldMap[(int)(info->pos.vx - info->dir.vx * info->moveSpeed)][(int)(info->pos.vy)])
			info->pos.vx -= info->dir.vx * info->moveSpeed;
		if (!worldMap[(int)(info->pos.vx)][(int)(info->pos.vy - info->dir.vy * info->moveSpeed)])
			info->pos.vy -= info->dir.vy * info->moveSpeed;
	}
	if (info->key_d)
		rotateMyView(info, -info->rotSpeed);
	if (info->key_a)
		rotateMyView(info, info->rotSpeed);
	if (info->key_esc)
		exit(0);
}


int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	key_update(info);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}

int		key_release(int key, t_info *info)
{
	if (key == K_ESC)
		exit(0);
	else if (key == K_W)
		info->key_w = 0;
	else if (key == K_A)
		info->key_a = 0;
	else if (key == K_S)
		info->key_s = 0;
	else if (key == K_D)
		info->key_d = 0;
	return (0);
}


int	main(void)
{
	t_info info;

	init(&info);
	if (!setTexture(&info.texture))
		return (0);
	load_texture(&info);
	
	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);
	mlx_hook(info.win, X_EVENT_KEY_RELEASE, 0, &key_release, &info);

	mlx_loop(info.mlx);
}
