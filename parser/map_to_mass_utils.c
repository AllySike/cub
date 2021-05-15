/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_mass_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 20:55:06 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:35:37 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_scene *scene)
{
	t_map	*map;

	if (scene->map)
	{
		map = scene->map->next;
		while (scene->map)
		{
			free(scene->map->line);
			free(scene->map);
			scene->map = map;
			if (!map)
				break ;
			map = map->next;
		}
	}
}

static t_map	*ft_maplast(t_map *lst)
{
	while (lst && lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

static t_map	*ft_mapnew(char *content)
{
	t_map	*elem;

	elem = (t_map *)malloc(sizeof(t_map));
	if (elem == NULL)
		return (NULL);
	elem->len = ft_strlen(content);
	(*elem).line = ft_strdup(content);
	(*elem).next = NULL;
	return (elem);
}

static void	ft_mapadd_back(t_map **lst, t_map *new)
{
	void	*f;

	if (lst)
	{
		if (!*lst && new)
		{
			*lst = new;
		}
		else if (new)
		{
			f = *lst;
			*lst = ft_maplast(*lst);
			(*lst)->next = new;
			*lst = f;
		}
	}
}

void	handle_map(char *line, t_scene *scene, int fd)
{
	int	rd;

	scene->map = ft_mapnew(line);
	rd = get_next_line(fd, &line);
	while (rd >= 0 && *line && *line != '\n')
	{
		ft_mapadd_back(&(scene->map), ft_mapnew(line));
		free(line);
		rd = get_next_line(fd, &line);
	}
	while (rd)
	{
		if (line && *line && *line != '\n')
			map_error(fd, scene, line);
		free(line);
		rd = get_next_line(fd, &line);
	}
	if (line && *line && *line != '\n')
		map_error(fd, scene, line);
	free(line);
}
