/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:43:04 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:43:36 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_check_diagonal_walls(t_scene *scene, int i, int j)
{
	if ((j > 0 && !(scene->mass[i][j - 1] == '0' || scene->mass[i][j - 1]
		== '1' || scene->mass[i][j - 1] == '2')) || (j > 0 && i > 0
		&& !(scene->mass[i - 1][j - 1] == '0' || scene->mass[i - 1][j - 1]
		== '1' || scene->mass[i - 1][j - 1] == '2')) || (j > 0 && i
		< scene->mass_y && !(scene->mass[i + 1][j - 1] == '0'
		|| scene->mass[i + 1][j - 1] == '1' || scene->mass[i + 1][j - 1]
		== '2')) || (j < scene->mass_x && !(scene->mass[i][j + 1] == '0'
		|| scene->mass[i][j + 1] == '1' || scene->mass[i][j + 1] == '2'))
		|| (j < scene->mass_x && i > 0 && !(scene->mass[i - 1][j + 1] == '0'
		|| scene->mass[i - 1][j + 1] == '1' || scene->mass[i - 1][j + 1]
		== '2')) || (j < scene->mass_x && i < scene->mass_y
		&& !(scene->mass[i + 1][j + 1] == '0' || scene->mass[i + 1][j + 1]
		== '1' || scene->mass[i + 1][j + 1] == '2')) || (i > 0
		&& !(scene->mass[i - 1][j] == '0' || scene->mass[i - 1][j] == '1'
		|| scene->mass[i - 1][j] == '2')) || (i < scene->mass_y
		&& !(scene->mass[i][j + 1] == '0' || scene->mass[i][j + 1] == '1'
		|| scene->mass[i][j + 1] == '2')))
		return (0);
	return (1);
}

void	ft_check_walls(t_scene *scene)
{
	int	i;
	int	j;

	i = 0;
	while (i <= scene->mass_y)
	{
		j = 0;
		while (j <= scene->mass_x)
		{
			if (scene->mass[i][j] == '0' || scene->mass[i][j] == '2')
			{
				if ((!ft_check_diagonal_walls(scene, i, j)))
					error_with_map(scene);
			}
			j++;
		}
		i++;
	}
}
