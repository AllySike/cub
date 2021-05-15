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
	scene->mass[y][x] = '0';
	scene->player.x = x * SIZE_CHUNK;
	scene->player.y = y * SIZE_CHUNK;
}

static int ft_check_diagonal_walls(t_scene *scene, int i, int j)
{
	if ((j > 0 && !(scene->mass[i][j - 1] == '0' || scene->mass[i][j - 1] == '1'
		|| scene->mass[i][j - 1] == '2')) || (j > 0 && i > 0 && !(scene->mass[i - 1][j - 1] == '0'
		|| scene->mass[i - 1][j - 1] == '1' || scene->mass[i - 1][j - 1] == '2')) || (j > 0
		&& i < scene->mass_y && !(scene->mass[i + 1][j - 1] == '0' || scene->mass[i + 1][j - 1] == '1'
		|| scene->mass[i + 1][j - 1] == '2')) || (j < scene->mass_x && !(scene->mass[i][j + 1] == '0'
		|| scene->mass[i][j + 1] == '1' || scene->mass[i][j + 1] == '2'))
		|| (j < scene->mass_x && i > 0 && !(scene->mass[i - 1][j + 1] == '0' || scene->mass[i - 1][j + 1] == '1'
		|| scene->mass[i - 1][j + 1] == '2')) || (j < scene->mass_x && i < scene->mass_y
		&& !(scene->mass[i + 1][j + 1] == '0' || scene->mass[i + 1][j + 1] == '1' || scene->mass[i + 1][j + 1] == '2'))
		|| (i > 0 && !(scene->mass[i - 1][j] == '0' || scene->mass[i - 1][j] == '1' || scene->mass[i - 1][j] == '2'))
		|| (i < scene->mass_y && !(scene->mass[i][j + 1] == '0' || scene->mass[i][j + 1] == '1'
		|| scene->mass[i][j + 1] == '2')))
		return (0);
	return (1);
}

static void	ft_check_walls(t_scene *scene)
{
    int i;
    int j;

    i = 0;
    while (i <= scene->mass_y)
    {
        j = 0;
        while(j <= scene->mass_x)
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

void	mass_from_map(t_scene *scene, t_map   *map, int ii)
{
	int		i;
	char	c;
	char	*mass;

	i = 0;
	while (map->line[i])
	{
		c = map->line[i];
		if (c == '0' || c == '1' || c == ' ')
			scene->mass[ii][i] = c;
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
	scene->mass_y = j - 1;
	scene->mass_x = max - 1;
	i = 0;
	while (i < j)
	{
		scene->mass[i] = calloc(max, sizeof(char));
		mass_from_map(scene, tmp, i);
		tmp = tmp->next;
		i++;
	}
    ft_check_walls(scene);
	scene->mass[i] = NULL;
}
