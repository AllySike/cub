/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:52:26 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:54:54 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	render_next_frame(t_all *all)
{
	ft_reycast(all);
	if (all->scene->save_option == 1)
	{
		create_bmp(all);
		ft_close_exit(all);
	}
	mlx_put_image_to_window(all->vars.mlx, all->vars.win, all->data.img, 0, 0);
	if (all->key.keycode >= 0)
	{
		mlx_destroy_image(all->vars.mlx, all->data.img);
		all->data.img = mlx_new_image(all->vars.mlx,
				all->scene->x_rea, all->scene->y_rea);
		all->data.addr = mlx_get_data_addr(all->data.img,
				&all->data.bits_per_pixel, &all->data.line_length,
				&all->data.endian);
		move(all);
	}
	return (0);
}

static int	ft_key_hook(int keycode, t_all *all)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(all->vars.mlx, all->vars.win);
		free(all->vis.rey_len);
		if (all->sprite != NULL)
			free_sprite(all);
		exit(-1);
	}
	if (keycode == W || keycode == S || keycode == A
		|| keycode == D || keycode == TURN_LEFT
		|| keycode == TURN_RIGHT)
		all->key.keycode = keycode;
	return (0);
}

static int	ft_key_stop(int keycode, t_all *all)
{
	if (keycode == W || keycode == S || keycode == A
		|| keycode == D || keycode == TURN_LEFT
		|| keycode == TURN_RIGHT)
		all->key.keycode = -1;
	return (0);
}

static void	consist_map(t_all *all)
{
	while (all->scene->mass[++all->map_length.y] != NULL)
	{
		all->map_length.x = -1;
		while (all->scene->mass[all->map_length.y][++all->map_length.x] != '\0')
			save_sprite_list(all);
	}
}

int	ft_window(t_scene *scene)
{
	t_all	all;

	all.vars.mlx = mlx_init();
	if (all.vars.mlx == NULL)
	{
		printf("Error\nLibrary initialization mlx. \n");
		free_scene(scene);
		exit (-1);
	}
	check_scene(scene);
	all.scene = scene;
	if (all_null(&all) == -1)
		return (-1);
	if (all_null(&all) == -1)
		return (-1);
	consist_map(&all);
	mlx_loop_hook(all.vars.mlx, render_next_frame, &all);
	if (scene->save_option != 1)
	{
		mlx_hook(all.vars.win, 2, 1L << 0, ft_key_hook, &all);
		mlx_hook(all.vars.win, 3, 1L << 1, ft_key_stop, &all);
		mlx_hook(all.vars.win, CLOSE, 0, ft_close_exit, &all);
	}
	mlx_loop(all.vars.mlx);
	return (0);
}
