/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 19:47:45 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:57:50 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_scene(t_scene **scene)
{
	*scene = (t_scene *)malloc(sizeof(t_scene));
	(*scene)->x_rea = -1;
	(*scene)->y_rea = -1;
	(*scene)->NO_texture = NULL;
	(*scene)->SO_texture = NULL;
	(*scene)->WE_texture = NULL;
	(*scene)->EA_texture = NULL;
	(*scene)->S_texture = NULL;
	(*scene)->floor = -1;
	(*scene)->ceiling = -1;
	(*scene)->pl.x = -1;
	(*scene)->pl.y = -1;
	(*scene)->pl.angl = -1;
	(*scene)->mass_x = -1;
	(*scene)->mass_y = -1;
	(*scene)->save_option = 0;
}

void	check_scene(t_scene *scene)
{
	int	max_size_x;
	int	max_size_y;

	if (!scene || scene->x_rea == -1 || scene->y_rea == -1
		|| scene->NO_texture == NULL || scene->SO_texture == NULL
		|| scene->WE_texture == NULL || scene->EA_texture == NULL
		|| scene->S_texture == NULL || scene->floor == -1
		|| scene->ceiling == -1 || scene->pl.x == -1
		|| scene->pl.y == -1 || scene->pl.angl == -1
		|| scene->mass_x == -1 || scene->mass_y == -1)
		error_with_map(scene);
	mlx_get_screen_size(&max_size_x, &max_size_y);
	if (scene->save_option != 1
		&& (scene->x_rea > max_size_x))
		scene->x_rea = max_size_x;
	if (scene->save_option != 1
		&& (scene->y_rea > max_size_y))
		scene->y_rea = max_size_y;
}

void	ft_parser(int fd, t_scene *scene)
{
	int		gnl;
	char	*line;

	gnl = get_next_line((const int)fd, &line);
	while (gnl > 0)
	{
		line_parser(line, scene, fd);
		free(line);
		gnl = get_next_line((const int)fd, &line);
	}
	free(line);
	close(fd);
	map_to_mass(scene);
}
