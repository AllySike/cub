/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_mass.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:48:51 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 12:03:45 by kgale            ###   ########.fr       */
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

static void set_player(int x, int y, char c, t_scene *scene)
{
	if (c == 'N')
		scene->player.angle = 0;
	else if (c == 'S')
		scene->player.angle = 180;
	else if (c != 'W')
		scene->player.angle = 270;
	else if (c != 'E')
		scene->player.angle = 90;
	scene->player.x = x * SIZE_CHUNK;
	scene->player.y = y * SIZE_CHUNK;
}

static void	ft_check_walls(int i, int j, t_scene *scene)
{
	if ((scene->mass[i - 1][j] != '1' && scene->mass[i - 1][j] != ' ')
			&& (scene->mass[i - 1][j - 1] != '1' && scene->mass[i - 1][j - 1] != ' ')
			&& (scene->mass[i][j - 1] != '1' && scene->mass[i][j - 1] != ' ')
			&& (scene->mass[i + 1][j - 1] != '1' && scene->mass[i + 1][j - 1] != ' ')
			&& (scene->mass[i + 1][j] != '1' && scene->mass[i + 1][j] != ' ')
			&& (scene->mass[i + 1][j + 1] != '1' && scene->mass[i + 1][j + 1] != ' ')
			&& (scene->mass[i][j + 1] != '1' && scene->mass[i][j + 1] != ' ')
			&& (scene->mass[i - 1][j + 1] != '1' && scene->mass[i - 1][j + 1] != ' '))
			error_with_map(scene);
}

void	mass_from_map(t_scene *scene, t_map   *map, int ii)
{
	int		i;
	char	c;
	char	*mass;

	i = 0;
	while (map->line[i])
	{
		c = map->line[i];
		if (c == '0' || c == '1')
			scene->mass[ii][i] = c;
		if (c == ' ')
			ft_check_walls(ii, i, scene);
		else if (c == '2')
			scene->mass[ii][i] = c;
		else if ((c == 'N' || c == 'S' || c == 'W' || c == 'E') && scene->player.x < 0)
			set_player(i, ii, c, scene);
		else
			error_with_map(scene);
		i++;
	}
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
	scene->mass = (char **)malloc(sizeof(char*) * (j + 1));
	scene->mass_y = j;
	scene->mass_x = max;
	i = 0;
	while (i < j)
	{
		scene->mass[i] = calloc(max, sizeof(char));
		mass_from_map(scene, tmp, i);
		tmp = tmp->next;
		i++;
	}
	scene->mass[i] = NULL;
}
