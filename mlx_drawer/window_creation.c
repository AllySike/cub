/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:29:02 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 23:53:44 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	all_addr(t_all *all)
{
	all->SO_texture.addr = mlx_get_data_addr(all->SO_texture.img,
			&all->SO_texture.bits_per_pixel, &all->SO_texture.line_length,
			&all->SO_texture.endian);
	all->EA_texture.addr = mlx_get_data_addr(all->EA_texture.img,
			&all->EA_texture.bits_per_pixel, &all->EA_texture.line_length,
			&all->EA_texture.endian);
	all->WE_texture.addr = mlx_get_data_addr(all->WE_texture.img,
			&all->WE_texture.bits_per_pixel, &all->WE_texture.line_length,
			&all->WE_texture.endian);
	all->NO_texture.addr = mlx_get_data_addr(all->NO_texture.img,
			&all->NO_texture.bits_per_pixel, &all->NO_texture.line_length,
			&all->NO_texture.endian);
	all->S_texture.addr = mlx_get_data_addr(all->S_texture.img,
			&all->S_texture.bits_per_pixel, &all->S_texture.line_length,
			&all->S_texture.endian);
}

static void	all_window(t_all *all)
{
	if (all->scene->save_option != 1)
		all->vars.win = mlx_new_window(all->vars.mlx,
				all->scene->x_rea, all->scene->y_rea, "cub3D");
	all->data.img = mlx_new_image(all->vars.mlx, all->scene->x_rea,
			all->scene->y_rea);
	all->data.addr = mlx_get_data_addr(all->data.img,
			&all->data.bits_per_pixel,
			&all->data.line_length, &all->data.endian);
	all->vis.ray_len = (double *)malloc(sizeof(double)
			* all->scene->x_rea);
	if (all->vis.ray_len == NULL)
	{
		printf("Error:\nMalloc failed");
		free_scene(all->scene);
		exit(-1);
	}
}

static void	all_image(t_all *all)
{
	all->SO_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
			all->scene->SO_texture,
			&all->SO_texture.width, &all->SO_texture.height);
	all->WE_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
			all->scene->WE_texture,
			&all->WE_texture.width, &all->WE_texture.height);
	all->EA_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
			all->scene->EA_texture,
			&all->EA_texture.width, &all->EA_texture.height);
	all->S_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
			all->scene->S_texture,
			&all->S_texture.width, &all->S_texture.height);
	all->NO_texture.img = mlx_xpm_file_to_image(all->vars.mlx,
			all->scene->NO_texture,
			&all->NO_texture.width, &all->NO_texture.height);
}

int	all_null(t_all *all)
{
	all->sprite = NULL;
	all->vis.check_sprite = 0;
	all->vis.count_sprite = 0;
	all->map_length.x = -1;
	all->map_length.y = -1;
	all->pix_for_map.x = 0;
	all->pix_for_map.y = 0;
	all_window(all);
	all_image(all);
	if (all->WE_texture.img == NULL || all->EA_texture.img == NULL
		|| all->NO_texture.img == NULL || all->SO_texture.img == NULL
		|| all->S_texture.img == NULL)
	{
		print_error(all);
		return (-1);
	}
	all_addr(all);
	return (0);
}
