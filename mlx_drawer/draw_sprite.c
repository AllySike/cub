/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:15:24 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:56:19 by kgale            ###   ########.fr       */
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
			|| all->sprite->start + i >= all->scene->x_rea
			|| all->vis.rey_len[all->sprite->start + i] < all->sprite->dist)
			continue ;
		j = -1;
		while (j < all->sprite->size - 1)
		{
			j++;
			if (all->sprite->y_start + j < 0
				|| all->sprite->y_start + j >= all->scene->y_rea)
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

void	save_sprite_list(t_all *all)
{
	t_sprite	*new;

	if (all->scene->mass[all->map_length.y][all->map_length.x] == '2')
	{
		new = all->sprite;
		while (all->sprite != NULL)
			all->sprite = all->sprite->next;
		all->sprite = (t_sprite *)malloc(sizeof(t_sprite));
		if (all->sprite == NULL)
			exit(-1);
		all->sprite->x = all->map_length.x * SIZE_CHUNK + (SIZE_CHUNK / 2.0);
		all->sprite->y = all->map_length.y * SIZE_CHUNK + (SIZE_CHUNK / 2.0);
		all->sprite->next = new;
	}
}
