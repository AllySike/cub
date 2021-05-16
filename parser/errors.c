/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:50:56 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 12:21:01 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_with_map(t_scene *scene)
{
	write(STDERR_FILENO, "Error\nWrong map format\n", 23);
	free_scene(scene);
	exit(-1);
}

void	map_error(int fd, t_scene *scene, char *line)
{
	if (line)
		free(line);
	if (fd > 0)
		close(fd);
	error_with_map(scene);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->SO_texture)
		free(scene->SO_texture);
	if (scene->NO_texture)
		free(scene->NO_texture);
	if (scene->EA_texture)
		free(scene->EA_texture);
	if (scene->WE_texture)
		free(scene->WE_texture);
	if (scene->S_texture)
		free(scene->S_texture);
	if (scene)
		free_map(scene);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		split[i] = NULL;
		i++;
	}
}

void	ft_exit(int fd, char **split, char *line)
{
	write(STDERR_FILENO, "Error\nWrong info format in the map\n", 35);
	if (split)
		free_split(split);
	if (fd > 0)
		close(fd);
	if (line && *line)
		free(line);
	exit(-1);
}
