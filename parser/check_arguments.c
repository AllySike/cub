/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:26:43 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 15:27:49 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_check_save(t_scene *scene, char *argv, int *fd)
{
	if (argv[0] && argv[1] && argv[2] && argv[3] && argv[4] && argv[5]
		&& argv[0] == '-' && argv[1] == '-' && argv[2] == 's' && argv[3] == 'a'
		&& argv[4] == 'v' && argv[5] == 'e' && !argv[6])
		scene->save_option = 1;
	else
	{
		write(STDERR_FILENO, "Error\nWrong save argument\n", 27);
		close(*fd);
		exit(-1);
	}
}

static void	check_errors_with_extentions(char *argv[])
{
	int	i;

	i = 0;
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (!argv[1][i])
	{
		write(STDERR_FILENO, "Error\nExtension needed\n", 23);
		exit(-1);
	}
	else if (i < 3 || argv[1][i] != '.' || !argv[1][i + 1]
		|| argv[1][i + 1] != 'c' || !argv[1][i + 2]
		|| argv[1][i + 2] != 'u' || !argv[1][i + 3]
		|| argv[1][i + 3] != 'b' || argv[1][i + 4])
	{
		write(STDERR_FILENO, "Error\nInvalid extension\n", 24);
		exit(-1);
	}
}

void	ft_check_argv(int argc, char **argv, t_scene **scene, int *fd)
{
	if (argc < 2 || argc > 3)
	{
		write(STDERR_FILENO, "Error\nWrong number of arguments\n", 32);
		exit(-1);
	}
	check_errors_with_extentions(argv);
	*fd = open(argv[1], O_RDONLY);
	if (*fd <= 0)
	{
		write(STDERR_FILENO, "Error\nNo such file or directory\n", 32);
		exit(-1);
	}
	init_scene(scene);
	if (!*scene)
	{
		write(STDERR_FILENO, "Error\nMalloc for scene failed\n", 31);
		exit(-1);
	}
	if (argc == 3)
		ft_check_save(*scene, argv[2], fd);
}
