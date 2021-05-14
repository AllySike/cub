/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:15:24 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 11:16:27 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	print_texture_sprite(t_all *all)
{
	int	j;
	int	i;

	i = -1;
	while (i < all->sprite->size - 1)
	{
		i++;
		if (all->sprite->start + i < 0
			|| all->sprite->start + i >= all->scene->x_resolution
			|| all->visual.rey_len[all->sprite->start + i] < all->sprite->dist)
			continue ;
		j = -1;
		while (j < all->sprite->size - 1)
		{
			j++;
			if (all->sprite->y_start + j < 0
				|| all->sprite->y_start + j >= all->scene->y_resolution)
				continue ;
			my_mlx_pixel_put(&all->data, (int)(all->sprite->start + i),
				(int)(all->sprite->y_start + j),
				(int)get_color_image(&all->S_texture,
					(int)(i * all->S_texture.width / all->sprite->size),
					(int)(j * all->S_texture.height / all->sprite->size)));
		}
	}
}

void	draw_sprite(t_all *all)
{
	t_sprite	*tmp;

	tmp = all->sprite;
	while (all->sprite != NULL)
	{
		print_texture_sprite(all);
		all->sprite = all->sprite->next;
	}
	all->sprite = tmp;
}
