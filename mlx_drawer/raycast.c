/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:27:37 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 23:48:32 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_abscissa(t_all *all, t_raycast *abscissa, double sin_a)
{
	double	tmp;

	tmp = all->scene->pl.y;
	while (1)
	{
		abscissa->dist_y = floor(tmp / SIZE_CHUNK)
			* SIZE_CHUNK + (abscissa->step * SIZE_CHUNK);
		if (sin_a < 0)
			abscissa->dist_y += SIZE_CHUNK - SIZE_PLAYER;
		abscissa->dist = fabs(abscissa->dist_y - tmp) / sin_a;
		abscissa->hypotenuse += (abscissa->dist * cos(all->vis.ugl)
				* (abscissa->step));
		if (abscissa->hypotenuse < 0 || abscissa->dist_y < 0
			|| (abscissa->hypotenuse / SIZE_CHUNK >= all->scene->mass_x)
			|| (abscissa->dist_y / SIZE_CHUNK >= all->map_length.y))
			break ;
		if (all->scene->mass[(int)(floor(abscissa->dist_y) / SIZE_CHUNK)]
			[(int)(floor(abscissa->hypotenuse) / SIZE_CHUNK)] == '1')
			break ;
		if (all->scene->mass[(int)(floor(abscissa->dist_y) / SIZE_CHUNK)]
			[(int)(floor(abscissa->hypotenuse) / SIZE_CHUNK)] == '2')
			all->vis.check_sprite = 1;
		tmp = abscissa->dist_y;
	}
}

static void	ft_ordinate(t_all *all, t_raycast *ordinate, double cos_a)
{
	double	tmp;

	tmp = all->scene->pl.x;
	while (1)
	{
		ordinate->dist_x = floor(tmp / SIZE_CHUNK)
			* SIZE_CHUNK + (ordinate->step * SIZE_CHUNK);
		if (cos_a < 0)
			ordinate->dist_x += SIZE_CHUNK - SIZE_PLAYER;
		ordinate->dist = fabs(ordinate->dist_x - tmp) / cos_a;
		ordinate->hypotenuse += (ordinate->dist * sin(all->vis.ugl)
				* (ordinate->step));
		if (ordinate->hypotenuse < 0 || ordinate->dist_x < 0
			|| (ordinate->hypotenuse / SIZE_CHUNK >= all->map_length.y))
			break ;
		if (all->scene->mass[(int)(floor(ordinate->hypotenuse) / SIZE_CHUNK)]
			[(int)(floor(ordinate->dist_x) / SIZE_CHUNK)] == '1')
			break ;
		if (all->scene->mass[(int)(floor(ordinate->hypotenuse) / SIZE_CHUNK)]
			[(int)(floor(ordinate->dist_x) / SIZE_CHUNK)] == '2')
			all->vis.check_sprite = 1;
		tmp = ordinate->dist_x;
	}
}

static void	raycast_utils(t_all *all, t_raycast *abscissa, t_raycast *ordinate)
{
	double		cos_a;
	double		sin_a;

	cos_a = cos(all->vis.ugl);
	sin_a = sin(all->vis.ugl);
	ordinate->hypotenuse = all->scene->pl.y + SIZE_PLAYER;
	abscissa->hypotenuse = all->scene->pl.x + SIZE_PLAYER;
	abscissa->step = -1;
	ordinate->step = -1;
	if (cos_a >= 0)
	{
		ordinate->step = 1;
		abscissa->hypotenuse = all->scene->pl.x;
		ordinate->hypotenuse = all->scene->pl.y;
	}
	if (sin_a >= 0)
	{
		abscissa->step = 1;
		abscissa->hypotenuse = all->scene->pl.x;
		ordinate->hypotenuse = all->scene->pl.y;
	}
	ft_ordinate(all, ordinate, cos_a);
	ft_abscissa(all, abscissa, sin_a);
}

void	ft_raycast(t_all *all)
{
	double		step;
	t_raycast	abscissa;
	t_raycast	ordinate;

	all->vis.ugl = (all->scene->pl.angl - (int)FOV2) * (RADS);
	all->vis.dist_screen = (all->scene->x_rea / 2.0)
		/ tan((int)(FOV / 2) *(RADS));
	all->vis.width = 0;
	step = (FOV * (RADS)) / (all->scene->x_rea - 1);
	while (all->vis.ugl <= ((all->scene->pl.angl + (int)(FOV / 2)) * RADS))
	{
		raycast_utils(all, &abscissa, &ordinate);
		abscissa.l = sqrt(pow((all->scene->pl.x - abscissa.hypotenuse), 2)
				+ pow((all->scene->pl.y - abscissa.dist_y), 2));
		ordinate.l = sqrt(pow((all->scene->pl.x - ordinate.dist_x), 2)
				+ pow((all->scene->pl.y - ordinate.hypotenuse), 2));
		if (fabs(abscissa.l) < fabs(ordinate.l))
			draw(all, abscissa.hypotenuse, abscissa.dist_y, abscissa.l);
		else
			draw(all, ordinate.dist_x, ordinate.hypotenuse, ordinate.l);
		all->vis.ugl += step;
		all->vis.width++;
	}
	if (all->vis.check_sprite == 1)
		check_sprite(all, step);
}
