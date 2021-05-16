/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_mass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:48:51 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 23:39:40 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_mapsize(t_map *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	else
	{
		while (lst && lst->next)
		{
			lst = lst->next;
			i++;
			if (!lst->next)
				return (i + 1);
		}
	}
	return (i + 1);
}

static void	set_player(int x, int y, char c, t_scene *scene)
{
	if (c == 'N')
		scene->pl.angl = 270;
	else if (c == 'S')
		scene->pl.angl = 90;
	else if (c != 'W')
		scene->pl.angl = 0;
	else if (c != 'E')
		scene->pl.angl = 180;
	scene->mass[y][x] = '0';
	scene->pl.x = x * SIZE_CHUNK + SIZE_CHUNK / 2;
	scene->pl.y = y * SIZE_CHUNK + SIZE_CHUNK / 2;
}

void	mass_from_map(t_scene *scene, t_map *map, int ii)
{
	int		i;
	char	c;

	i = 0;
	while (map->line[i])
	{
		c = map->line[i];
		if (c == '0' || c == '1' || c == ' ')
			scene->mass[ii][i] = c;
		else if (c == '2')
			scene->mass[ii][i] = c;
		else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E')
			&& scene->pl.x < 0)
			set_player(i, ii, c, scene);
		else
			error_with_map(scene);
		i++;
	}
}

static void	mass_init(t_scene *scene, int j, int max)
{
	scene->mass = (char **)malloc(sizeof(char *) * (j + 1));
	if (!scene->mass)
	{
		printf("Error:Malloc for map failed\n");
		free_scene(scene);
		exit (-1);
	}
	scene->mass_y = j - 1;
	scene->mass_x = max - 1;
}

void	map_to_mass(t_scene *scene)
{
	t_map	*tmp;
	int		max;
	int		j;
	int		i;

	tmp = scene->map;
	max = 0;
	while (tmp)
	{
		if (max < tmp->len)
			max = tmp->len;
		tmp = tmp->next;
	}
	tmp = scene->map;
	j = ft_mapsize(scene->map);
	mass_init(scene, j, max);
	i = 0;
	while (i < j)
	{
		scene->mass[i] = calloc(max, sizeof(char));
		mass_from_map(scene, tmp, i++);
		tmp = tmp->next;
	}
	ft_check_walls(scene);
	scene->mass[i] = NULL;
}
