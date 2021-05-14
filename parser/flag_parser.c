/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:47:00 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 12:36:22 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	handle_color(char *line, t_scene *scene, int fd)
{
	char	**split;
	char	**color;

	split = ft_split(line, ' ');
	if (!split[0] || !split[1] || split[2])
		ft_exit(fd, split, line);
	color = ft_split(split[1], ',');
	if (!color[0] || !color[1] || !color[2] || color[3]
		|| !ft_aredigits(color[0]) || !ft_aredigits(color[1])
		|| !ft_aredigits(color[2]) || (line[0] == 'F' && scene->floor >= 0)
		|| (line[0] == 'C' && scene->ceiling >= 0))
	{
		free_split(color);
		ft_exit(fd, split, line);
	}
	if (line[0] == 'F')
		scene->floor = create_trgb(0, ft_atoi(color[0]),
				ft_atoi(color[1]), ft_atoi(color[2]));
	else if (line[0] == 'C')
		scene->ceiling = create_trgb(0, ft_atoi(color[0]),
				ft_atoi(color[1]), ft_atoi(color[2]));
	free_split(split);
	free_split(color);
}

static void	handle_textures(char *line, t_scene *scene, int fd, char **split)
{
	if (line[0] == 'W')
	{
		if (!split[0] || !split[1] || split[2]
			|| !ft_check_path_to_texture(split[1], split, line))
			ft_exit(fd, split, line);
		scene->WE_texture = ft_strdup(split[1]);
	}
	else if (line[0] == 'E')
	{
		if (!split[0] || !split[1] || split[2]
			|| !ft_check_path_to_texture(split[1], split, line))
			ft_exit(fd, split, line);
		scene->EA_texture = ft_strdup(split[1]);
	}
}

static void	handle_texture(char *line, t_scene *scene, int fd)
{
	char	**split;

	split = my_split(line);
	if (line[0] == 'N')
	{
		if (!split[0] || !split[1] || split[2]
			|| !ft_check_path_to_texture(split[1], split, line))
			ft_exit(fd, split, line);
		scene->NO_texture = ft_strdup(split[1]);
	}
	else if (line[0] == 'S')
	{
		if (!split[0] || !split[1] || split[2]
			|| !ft_check_path_to_texture(split[1], split, line))
			ft_exit(fd, split, line);
		scene->SO_texture = ft_strdup(split[1]);
	}
	else
		handle_textures(line, scene, fd, split);
	free_split(split);
}

static void	handle_res_tex_col(char *line, t_scene *scene, int fd)
{
	char	**split;

	if (line[0] == 'R')
	{
		split = ft_split(line, ' ');
		if (!split[0] || !split[1] || !split[2] || scene->x_resolution >= 0
			|| !ft_aredigits(split[1]) || !ft_aredigits(split[2]) || split[3])
			ft_exit(fd, split, line);
		scene->x_resolution = ft_atoi(split[1]);
		scene->y_resolution = ft_atoi(split[2]);
		free_split(split);
	}
	else if (line[0] == 'S')
	{
		split = my_split(line);
		if (!split[0] || !split[1] || split[2] || scene->S_texture
			|| !ft_check_path_to_texture(split[1], split, line))
			ft_exit(fd, split, line);
		scene->S_texture = ft_strdup(split[1]);
		free_split(split);
	}
	else
		handle_color(line, scene, fd);
}

void	line_parser(char *line, t_scene *scene, int fd)
{
	if (line[0])
	{
		if ((line[0] == 'S' || line[0] == 'F' || line[0] == 'C'
				|| line[0] == 'R') && line[1] == ' ')
			handle_res_tex_col(line, scene, fd);
		// else if (line[2] && line[2] == ' '
		// 	&& ((line[0] == 'N' && line[1] == 'O')
		// 		|| (line[0] == 'S' && line[1] == 'O')
		// 		|| (line[0] == 'W' && line[1] == 'E')
		// 		|| (line[0] == 'E' && line[1] == 'A')))
		// 	handle_texture(line, scene, fd);
		// else if (line[0] == ' ' || line[0] == '1')
		// 	handle_map(&(*line), scene, fd);
		// else
		// {
		// 	close(fd);
		// 	free(line);
		// 	free_scene(scene);
		// 	write(STDERR_FILENO, "Error\nInvalid map\n", 18);
		// 	exit(-1);
		// }
	}
}
