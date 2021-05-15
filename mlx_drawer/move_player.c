/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 10:31:19 by kgale             #+#    #+#             */
/*   Updated: 2021/05/15 22:26:21 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_step_right(t_all	*all)
{
	int	x;
	int	y;

	x = all->scene->pl.x;
	y = all->scene->pl.y;
	if (all->key.keycode == D)
	{
		x += (STEP + 50) * cos((all->scene->pl.angl * RADS) + PI / 2);
		y += (STEP + 50) * sin((all->scene->pl.angl * RADS) + PI / 2);
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (0);
		x -= (STEP + 50) * cos((all->scene->pl.angl * RADS) + PI / 2);
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (1);
		y -= (STEP + 50) * sin((all->scene->pl.angl * RADS) + PI / 2);
		x += (STEP + 50) * cos((all->scene->pl.angl * RADS) + PI / 2);
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (2);
	}
	return (-1);
}

static int	check_step_left(t_all *all)
{
	int	x;
	int	y;

	x = all->scene->pl.x;
	y = all->scene->pl.y;
	if (all->key.keycode == A)
	{
		x -= (STEP + 50) * cos((all->scene->pl.angl * RADS) + PI / 2);
		y -= (STEP + 50) * sin((all->scene->pl.angl * RADS) + PI / 2);
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (0);
		x += (STEP + 50) * cos((all->scene->pl.angl * RADS) + PI / 2);
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (1);
		y += (STEP + 50) * sin((all->scene->pl.angl * RADS) + PI / 2);
		x -= (STEP + 50) * cos((all->scene->pl.angl * RADS) + PI / 2);
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (2);
	}
	if (all->key.keycode == D)
		return (check_step_right(all));
	return (-1);
}

static int	check_step_back(t_all *all)
{
	int	x;
	int	y;

	x = all->scene->pl.x;
	y = all->scene->pl.y;
	if (all->key.keycode == S)
	{
		x -= (STEP + 50) * cos((all->scene->pl.angl * RADS));
		y -= (STEP + 50) * sin((all->scene->pl.angl * RADS));
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (0);
		x += (STEP + 50) * cos((all->scene->pl.angl * RADS));
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (1);
		y += (STEP + 50) * sin((all->scene->pl.angl * RADS));
		x -= (STEP + 50) * cos((all->scene->pl.angl * RADS));
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (2);
	}
	if (all->key.keycode == D
		|| all->key.keycode == A)
	{
		return (check_step_left(all));
	}
	return (-1);
}

static int	check_step_fwd(t_all *all)
{
	int	x;
	int	y;

	x = all->scene->pl.x;
	y = all->scene->pl.y;
	if (all->key.keycode == W)
	{
		x += (STEP + 50) * cos((all->scene->pl.angl * RADS));
		y += (STEP + 50) * sin((all->scene->pl.angl * RADS));
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (0);
		x -= (STEP + 50) * cos((all->scene->pl.angl * RADS));
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (1);
		y -= (STEP + 50) * sin((all->scene->pl.angl * RADS));
		x += (STEP + 50) * cos((all->scene->pl.angl * RADS));
		if (all->scene->mass[y / SIZE_CHUNK][x / SIZE_CHUNK] != '1')
			return (2);
		return (-1);
	}
	if (all->key.keycode == S || all->key.keycode == D
		|| all->key.keycode == A)
		return (check_step_back(all));
	return (0);
}

void	move(t_all *all)
{
	int	i;

	i = check_step_fwd(all);
	if (all->key.keycode == W && i == 0)
	{
		all->scene->pl.x += STEP * cos((all->scene->pl.angl * RADS));
		all->scene->pl.y += STEP * sin((all->scene->pl.angl * RADS));
	}
	if (all->key.keycode == W && i == 1)
		all->scene->pl.y += STEP * sin((all->scene->pl.angl * RADS));
	if (all->key.keycode == W && i == 2)
		all->scene->pl.x += STEP * cos((all->scene->pl.angl * RADS));
	if (all->key.keycode == S && i == 0)
	{
		all->scene->pl.x -= STEP * cos((all->scene->pl.angl * RADS));
		all->scene->pl.y -= STEP * sin((all->scene->pl.angl * RADS));
	}
	if (all->key.keycode == S && i == 1)
		all->scene->pl.y -= STEP * sin((all->scene->pl.angl * RADS));
	if (all->key.keycode == S && i == 2)
		all->scene->pl.x -= STEP * cos((all->scene->pl.angl * RADS));
	if (all->key.keycode == D || all->key.keycode == A
		|| all->key.keycode == TURN_RIGHT || all->key.keycode == TURN_LEFT)
		move_utils(all, i);
}
