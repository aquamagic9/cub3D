/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 21:55:30 by junseo            #+#    #+#             */
/*   Updated: 2022/11/28 00:15:40 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/bonus/cub3d_bonus.h"

void	set_color(t_color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

int	switch_color(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

void	load_image(t_window *window, int *texture, char *path, t_img *img)
{
	int	y;
	int	x;

	img->img = mlx_xpm_file_to_image(window->mlx, path, \
		&img->img_width, &img->img_height);
	if (img->img == NULL)
		exit_with_error("error occurred during read image file");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
		&img->size_l, &img->endian);
	y = -1;
	while (++y < img->img_height)
	{
		x = -1;
		while (++x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(window->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(&info->window, info->window.texture[D_NORTH], \
		info->texture_file[D_NORTH], &img);
	load_image(&info->window, info->window.texture[D_SOUTH], \
		info->texture_file[D_SOUTH], &img);
	load_image(&info->window, info->window.texture[D_EAST], \
		info->texture_file[D_EAST], &img);
	load_image(&info->window, info->window.texture[D_WEST], \
		info->texture_file[D_WEST], &img);
}
