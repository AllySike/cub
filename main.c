/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 17:43:52 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:57:16 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_scene	*scene;
	int		fd;

	ft_check_argv(argc, argv, &scene, &fd);
	ft_parser(fd, scene);
	if (ft_window(scene) == -1)
		exit(-1);
	return (0);
}
