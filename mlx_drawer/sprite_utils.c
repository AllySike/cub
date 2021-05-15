/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:44:14 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:29:34 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	sort_help(t_sprite **pr, t_sprite **q, t_sprite **p, t_sprite **out)
{
	if (*pr == NULL)
	{
		(*q)->next = *out;
		*out = *q;
	}
	else
	{
		(*q)->next = *p;
		(*pr)->next = *q;
	}
}

static t_sprite	*sort_list(t_sprite *head)
{
	t_sprite	*q;
	t_sprite	*out;
	t_sprite	*p;
	t_sprite	*pr;

	out = NULL;
	while (head != NULL)
	{
		q = head;
		head = head->next;
		p = out;
		pr = NULL;
		while (p != NULL && q->dist <= p->dist)
		{
			pr = p;
			p = p->next;
		}
		sort_help(&pr, &q, &p, &out);
	}
	return (out);
}

static void	check_sprite_utils(t_all *all, double step)
{
	double	teta;

	teta = atan2(all->sprite->y - all->scene->pl.y,
			all->sprite->x - all->scene->pl.x);
	all->sprite->dist = sqrt(pow(all->sprite->x - all->scene->pl.x, 2)
			+ pow(all->sprite->y - all->scene->pl.y, 2));
	while (teta - (all->scene->pl.angl * (RADS)) > PI)
		teta -= 2 * PI;
	while (teta - (all->scene->pl.angl * (RADS)) < -PI)
		teta += 2 * PI;
	all->sprite->size = (int)round(((SIZE_CHUNK / 1.9)
				/ all->sprite->dist) * all->vis.dist_screen);
	all->sprite->start = (int)((all->scene->x_rea - 1) / 2.0
			+ (teta - (all->scene->pl.angl * (RADS)))
			/ step - all->sprite->size / 2.0);
	all->sprite->y_start = (all->scene->y_rea / 2)
		+ (all->sprite->size / SIZE_CHUNK);
	all->sprite = all->sprite->next;
}

void	check_sprite(t_all *all, double step)
{
	t_sprite	*tmp;

	tmp = all->sprite;
	while (all->sprite != NULL)
		check_sprite_utils(all, step);
	all->sprite = tmp;
	all->sprite = sort_list(all->sprite);
	draw_sprite(all);
	all->vis.check_sprite = 0;
}
