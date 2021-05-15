/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:55:49 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 23:48:32 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	wall_for_screen(t_all *all, t_map_texture *texture)
{
	if ((texture->x_mass + SIZE_CHUNK - SIZE_PLAYER
			<= (int)round(texture->x))
		&& (all->scene->mass[texture->y_mass / SIZE_CHUNK]
			[(texture->x_mass / SIZE_CHUNK) + 1] != '1'))
		my_mlx_pixel_put(&all->data, all->vis.width, texture->y_tmp,
			(int)get_color_image(&all->WE_texture,
				(int)all->WE_texture.color_x, (int)all->WE_texture.color_y));
	if (texture->y_mass + SIZE_CHUNK - SIZE_PLAYER == (int)round(texture->y)
		&& (all->scene->mass[(texture->y_mass / SIZE_CHUNK) + 1]
			[texture->x_mass / SIZE_CHUNK] != '1'))
		my_mlx_pixel_put(&all->data, all->vis.width, texture->y_tmp,
			(int)get_color_image(&all->NO_texture,
				(int)all->NO_texture.color_x, (int)all->NO_texture.color_y));
	if ((texture->y_mass == (int)round(texture->y))
		&& (all->scene->mass[(texture->y_mass / SIZE_CHUNK - 1)]
			[texture->x_mass / SIZE_CHUNK] != '1'))
		my_mlx_pixel_put(&all->data, all->vis.width, texture->y_tmp,
			(int)get_color_image(&all->SO_texture,
				(int)all->SO_texture.color_x, (int)all->SO_texture.color_y));
	if ((texture->x_mass == (int)round(texture->x))
		&& (all->scene->mass[texture->y_mass / SIZE_CHUNK]
			[(texture->x_mass / SIZE_CHUNK) - 1] != '1'))
		my_mlx_pixel_put(&all->data, all->vis.width, texture->y_tmp,
			(int)get_color_image(&all->EA_texture,
				(int)all->EA_texture.color_x, (int)all->EA_texture.color_y));
}

static void	draw_flag(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->scene->y_rea / 2)
		my_mlx_pixel_put(&all->data, all->vis.width, i++, all->scene->ceiling);
	while (i < all->scene->y_rea)
		my_mlx_pixel_put(&all->data, all->vis.width, i++, all->scene->floor);
}

static void	pull_texture_utils(t_all *all, t_map_texture *texture)
{
	if (SIZE_CHUNK > all->NO_texture.width)
		all->NO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->NO_texture.width));
	else
		all->NO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				* (all->NO_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->SO_texture.width)
		all->SO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->SO_texture.width));
	else
		all->SO_texture.color_x = (int)(((int)texture->x % SIZE_CHUNK)
				* (all->SO_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->EA_texture.width)
		all->EA_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->EA_texture.width));
	else
		all->EA_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				* (all->EA_texture.width / SIZE_CHUNK));
	if (SIZE_CHUNK > all->WE_texture.width)
		all->WE_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				/ (SIZE_CHUNK / all->WE_texture.width));
	else
		all->WE_texture.color_x = (int)(((int)texture->y % SIZE_CHUNK)
				* (all->WE_texture.width / SIZE_CHUNK));
}

static void	pull_texture(t_all *all, t_map_texture *texture, int h, int h_real)
{
	int	i;
	int	k;

	i = 0;
	pull_texture_utils(all, texture);
	draw_flag(all);
	while (texture->y_tmp >= (all->scene->y_rea / 2) - (h / 2)
		&& texture->y_tmp >= 0)
	{
		k = ((h + h_real) >> 1) - i;
		all->NO_texture.color_y = (int)((all->NO_texture.height - 1)
				* k / h_real);
		all->WE_texture.color_y = (int)((all->WE_texture.height - 1)
				* k / h_real);
		all->SO_texture.color_y = (int)((all->SO_texture.height - 1)
				* k / h_real);
		all->EA_texture.color_y = (int)((all->EA_texture.height - 1)
				* k / h_real);
		wall_for_screen(all, texture);
		texture->y_tmp--;
		i++;
	}
}

void	draw(t_all *all, double x, double y, double l)
{
	t_map_texture		texture;
	int					h;
	int					h_real;

	all->vis.ray_len[all->vis.width] = l;
	l *= cos(fabs(all->vis.ugl - (all->scene->pl.angl * (RADS))));
	h = (int)round((SIZE_CHUNK / l) * all->vis.dist_screen);
	h_real = h;
	if (h > all->scene->y_rea)
		h = all->scene->y_rea;
	texture.y_tmp = (all->scene->y_rea / 2) + (h / 2) - 1;
	texture.x_mass = (int)(round(x) / SIZE_CHUNK) *SIZE_CHUNK;
	texture.y_mass = (int)(round(y) / SIZE_CHUNK) *SIZE_CHUNK;
	if (x < 0)
		x = SIZE_CHUNK;
	if (y < 0)
		y = SIZE_CHUNK;
	texture.x = x;
	texture.y = y;
	pull_texture(all, &texture, h, h_real);
}
