/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:35:13 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:26:35 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_utils(t_all *all, int i)
{
	if (all->key.keycode == D && i == 0)
	{
		all->scene->pl.x += STEP * cos((all->scene->pl.angl * RADS) + PI / 2);
		all->scene->pl.y += STEP * sin((all->scene->pl.angl * RADS) + PI / 2);
	}
	if (all->key.keycode == D && i == 1)
		all->scene->pl.y += STEP * sin((all->scene->pl.angl * RADS) + PI / 2);
	if (all->key.keycode == D && i == 2)
		all->scene->pl.x += STEP * cos((all->scene->pl.angl * RADS) + PI / 2);
	if (all->key.keycode == A && i == 0)
	{
		all->scene->pl.x -= STEP * cos((all->scene->pl.angl * RADS) + PI / 2);
		all->scene->pl.y -= STEP * sin((all->scene->pl.angl * RADS) + PI / 2);
	}
	if (all->key.keycode == A && i == 1)
		all->scene->pl.y -= STEP * sin((all->scene->pl.angl * RADS) + PI / 2);
	if (all->key.keycode == A && i == 2)
		all->scene->pl.x -= STEP * cos((all->scene->pl.angl * RADS) + PI / 2);
	if (all->key.keycode == TURN_RIGHT)
		all->scene->pl.angl += 4;
	if (all->key.keycode == TURN_LEFT)
		all->scene->pl.angl -= 4;
}
