/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 19:47:45 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 15:29:21 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_scene(t_scene **scene)
{
	*scene = (t_scene *)malloc(sizeof(t_scene));
	(*scene)->x_resolution = -1;
	(*scene)->y_resolution = -1;
	(*scene)->NO_texture = NULL;
	(*scene)->SO_texture = NULL;
	(*scene)->WE_texture = NULL;
	(*scene)->EA_texture = NULL;
	(*scene)->S_texture = NULL;
	(*scene)->floor = -1;
	(*scene)->ceiling = -1;
	(*scene)->player.x = -1;
	(*scene)->player.y = -1;
	(*scene)->player.angle = -1;
	(*scene)->mass_x = -1;
    (*scene)->mass_y = -1;
    (*scene)->save_option = 0;
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


// int	main(int argc, char **argv)
// {
// 	t_scene	scene;
// 	int		fd;

// 	ft_check_argv(argc, argv, &scene, &fd);
// 	ft_parser(fd, &scene);
// 	///////////////////////////////////////
// 	// if (ft_window(file) == -1)
// 	// 	exit(-1);
// 	return (0);
// }
//gcc parser/parser.c parser/check_arguments.c mlx_drawer/mlx_utils.c libft/libft.a parser/errors.c parser/flag_parser.c \
parser/map_to_mass.c parser/flag_parser_utils.c parser/map_to_mass_utils.c && ./a.out map_examples/gay.cub
