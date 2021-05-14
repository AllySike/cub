/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:43:52 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 12:23:22 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static void	check_scene(t_scene *scene)
{
	int	max_size_x;
	int	max_size_y;
	if (!scene || scene->x_resolution == -1 || scene->y_resolution == -1
		||	scene->NO_texture == NULL || scene->SO_texture == NULL
		|| scene->WE_texture == NULL || scene->EA_texture == NULL
		|| scene->S_texture == NULL || scene->floor == -1
		|| scene->ceiling == -1 || scene->player.x == -1
		|| scene->player.y == -1 || scene->player.angle == -1
		|| scene->mass_x == -1 || scene->mass_y == -1)
		error_with_map(scene);
	mlx_get_screen_size(&max_size_x, &max_size_y);
	if (scene->save_option != 1
		&& (scene->x_resolution > max_size_x))
		scene->x_resolution = max_size_x;
	if (scene->save_option != 1
		&& (scene->y_resolution > max_size_y))
		scene->y_resolution = max_size_y;
}

void	save_sprite_list(t_all *all)
{
	t_sprite	*new;

	if (all->scene->mass[all->map_length.y][all->map_length.x] == '2')
	{
		new = all->sprite;
		while (all->sprite != NULL)
			all->sprite = all->sprite->next;
		all->sprite = (t_sprite *)malloc(sizeof(t_sprite));
		if (all->sprite == NULL)
			exit(-1);
		all->sprite->x = all->map_length.x * SIZE_CHUNK + (SIZE_CHUNK / 2.0);
		all->sprite->y = all->map_length.y * SIZE_CHUNK + (SIZE_CHUNK / 2.0);
		all->sprite->next = new;
	}
}

int	render_next_frame(t_all *all)
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
				all->scene->x_resolution, all->scene->y_resolution);
		all->data.addr = mlx_get_data_addr(all->data.img,
				&all->data.bits_per_pixel, &all->data.line_length,
				&all->data.endian);
		move(all);
	}
	return (0);
}

int	ft_key_hook(int keycode, t_all *all)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(all->vars.mlx, all->vars.win);
		free(all->visual.rey_len);
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

int	ft_key_stop(int keycode, t_all *all)
{
	if (keycode == W || keycode == S || keycode == A
		|| keycode == D || keycode == TURN_LEFT
		|| keycode == TURN_RIGHT)
		all->key.keycode = -1;
	return (0);
}

int	ft_window(t_scene *scene)
{
	t_all	*all;

	// all->vars.mlx = mlx_init();
	// if (all->vars.mlx == NULL)
	// {
	// 	printf("Error\nLibrary initialization mlx. \n");
	// 	free_scene(scene);
	// 	exit (-1);
	// }
	check_scene(scene);
	all->scene = scene;
	// save_sprite_list(all);
	// if (all_null(all) == -1)
	// 	return (-1);
	// mlx_loop_hook(all->vars.mlx, render_next_frame, all);
	// if (scene->save_option != 1)
	// {
	// 	mlx_hook(all->vars.win, 2, 1L << 0, ft_key_hook, all);
	// 	mlx_hook(all->vars.win, 3, 1L << 1, ft_key_stop, all);
	// 	mlx_hook(all->vars.win, CLOSE, 0, ft_close_exit, all);
	// }
	// mlx_loop(all->vars.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;
	int		fd;

	ft_check_argv(argc, argv, &scene, &fd);
	ft_parser(fd, scene);
	printf("%s", scene->mass[0]);
	///////////////////////////////////////
	if (ft_window(scene) == -1)
		exit(-1);
	return (0);
}

