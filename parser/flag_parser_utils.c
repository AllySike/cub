/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgale <kgale@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 21:04:23 by kgale             #+#    #+#             */
/*   Updated: 2021/05/13 21:04:56 by kgale            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_check_path_to_texture(char *path, char **split, char *line)
{
	int		fd;
	char	buff[1];

	if (!path[0])
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit(fd, split, line);
	fd = read(fd, buff, 0);
	if (fd < 0)
		ft_exit(fd, split ,line);
	close(fd);
	return (1) ;
}
