/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:23:50 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 10:26:44 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_close_exit(t_all *all)
{
	free(all->visual.rey_len);
	if (all->sprite != NULL)
		free_sprite(all);
	free_scene(all->scene);
	exit(0);
	return (0);
}

void	free_sprite(t_all *all)
{
	t_sprite	*tmp;

	while (all->sprite != NULL)
	{
		tmp = all->sprite->next;
		free(all->sprite);
		all->sprite = tmp;
	}
}

void	print_error(t_all *all)
{
	if (all == NULL)
	{
		printf("Error\nCheck your int in file\n");
		exit (-1);
	}
	if (all->NO_texture.img == NULL)
		printf("Error\nСould not read the wall texture file NO\n");
	if (all->SO_texture.img == NULL)
		printf("Error\nСould not read the wall texture file SO\n");
	if (all->WE_texture.img == NULL)
		printf("Error\nСould not read the wall texture file WE\n");
	if (all->EA_texture.img == NULL)
		printf("Error\nСould not read the wall texture file EA\n");
	if (all->S_texture.img == NULL)
		printf("Error\nСould not read sprite texture file S\n");
}
