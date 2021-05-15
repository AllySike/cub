/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:27:37 by kgale             #+#    #+#             */
/*   Updated: 2021/05/14 10:29:27 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_abscissa(t_all *all, t_reycast *abscissa, double sin_a)
{
	double	tmp;

	tmp = all->scene->player.y;
	while (1)
	{
		abscissa->dist_y = floor(tmp / SIZE_CHUNK)
			* SIZE_CHUNK + (abscissa->step * SIZE_CHUNK);
		if (sin_a < 0)
			abscissa->dist_y += SIZE_CHUNK - SIZE_PLAYER;
		abscissa->dist = fabs(abscissa->dist_y - tmp) / sin_a;
		abscissa->hypotenuse += (abscissa->dist * cos(all->visual.ugl)
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
			all->visual.check_sprite = 1;
		tmp = abscissa->dist_y;
	}
}

static void	ft_ordinate(t_all *all, t_reycast *ordinate, double cos_a)
{
	double	tmp;

	tmp = all->scene->player.x;
	while (1)
	{
		ordinate->dist_x = floor(tmp / SIZE_CHUNK)
			* SIZE_CHUNK + (ordinate->step * SIZE_CHUNK);
		if (cos_a < 0)
			ordinate->dist_x += SIZE_CHUNK - SIZE_PLAYER;
		ordinate->dist = fabs(ordinate->dist_x - tmp) / cos_a;
		ordinate->hypotenuse += (ordinate->dist * sin(all->visual.ugl)
				* (ordinate->step));
		if (ordinate->hypotenuse < 0 || ordinate->dist_x < 0
			|| (ordinate->hypotenuse / SIZE_CHUNK >= all->map_length.y))
			break ;
		if (all->scene->mass[(int)(floor(ordinate->hypotenuse) / SIZE_CHUNK)]
			[(int)(floor(ordinate->dist_x) / SIZE_CHUNK)] == '1')
			break ;
		if (all->scene->mass[(int)(floor(ordinate->hypotenuse) / SIZE_CHUNK)]
			[(int)(floor(ordinate->dist_x) / SIZE_CHUNK)] == '2')
			all->visual.check_sprite = 1;
		tmp = ordinate->dist_x;
	}
}

static void	reycast_utils(t_all *all, t_reycast *abscissa, t_reycast *ordinate)
{
	double		cos_a;
	double		sin_a;

	cos_a = cos(all->visual.ugl);
	sin_a = sin(all->visual.ugl);
	ordinate->hypotenuse = all->scene->player.y + SIZE_PLAYER;
	abscissa->hypotenuse = all->scene->player.x + SIZE_PLAYER;
	abscissa->step = -1;
	ordinate->step = -1;
	if (cos_a >= 0)
	{
		ordinate->step = 1;
		abscissa->hypotenuse = all->scene->player.x;
		ordinate->hypotenuse = all->scene->player.y;
	}
	if (sin_a >= 0)
	{
		abscissa->step = 1;
		abscissa->hypotenuse = all->scene->player.x;
		ordinate->hypotenuse = all->scene->player.y;
	}
	ft_ordinate(all, ordinate, cos_a);
	ft_abscissa(all, abscissa, sin_a);
}

void	ft_reycast(t_all *all)
{
	double		step;
	t_reycast	abscissa;
	t_reycast	ordinate;

	all->visual.ugl = (all->scene->player.angle - (int)FOV2) * (PI / 180);
	all->visual.dist_screen = (all->scene->x_resolution / 2.0)
		/ tan((int)(FOV / 2) *(PI / 180));
	all->visual.width = 0;
	step = (FOV * (PI / 180)) / (all->scene->x_resolution - 1);
	while (all->visual.ugl <= ((all->scene->player.angle + (int)(FOV / 2)) *(PI / 180)))
	{
		reycast_utils(all, &abscissa, &ordinate);
		abscissa.l = sqrt(pow((all->scene->player.x - abscissa.hypotenuse), 2)
				+ pow((all->scene->player.y - abscissa.dist_y), 2));
		ordinate.l = sqrt(pow((all->scene->player.x - ordinate.dist_x), 2)
				+ pow((all->scene->player.y - ordinate.hypotenuse), 2));
		if (fabs(abscissa.l) < fabs(ordinate.l))
			draw(all, abscissa.hypotenuse, abscissa.dist_y, abscissa.l);
		else
			draw(all, ordinate.dist_x, ordinate.hypotenuse, ordinate.l);
		all->visual.ugl += step;
		all->visual.width++;
	}
	if (all->visual.check_sprite == 1)
		check_sprite(all, step);
}
