/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:22:55 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/25 23:48:23 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"
#include "parse.h"
#include <sys/types.h>

static ssize_t	find_checkstart(char *line, t_data *data)
{
	ssize_t	x;
	int		enclosed;

	x = data->smap.x - 2;
	enclosed = 1;
	while (--x > 0 && data->map[x][0] == MAPEMPTY)
		enclosed = enclosed && (data->map[x][0] == MAPWALL ||
			data->map[x][0] == MAPEMPTY);
	if (!enclosed)
	{
		free(line);
		ft_error(EINVMAP, data);
	}
	return (x);
}

static void		check_endline(char *line, ssize_t x, ssize_t y, t_data *data)
{
	while (x < data->smap.x - 1)
	{
		if (data->map[x][y] != MAPEMPTY)
		{
			free(line);
			ft_error(EINVMAP, data);
		}
		x++;
	}
}

void			check_enclosed(char *line, t_data *data)
{
	ssize_t	x;
	ssize_t	y;

	x = find_checkstart(line, data);
	y = 0;
	while (y < data->smap.y - 1)
	{
		while (x < data->smap.x - 1 && data->map[x][y] == MAPWALL)
			x++;
		check_endline(line, x, y, data);
		x -= x > 0 ? 1 : 0;
		while (x > 0 && data->map[x][y] == MAPWALL && data->map[x][y + 1]
				== MAPEMPTY)
			x--;
		if (data->map[x][y + 1] != MAPWALL)
		{
			free(line);
			ft_error(EINVMAP, data);
		}
		y++;
	}
	while (x < data->smap.x - 1 && data->map[x][y] == MAPWALL)
		x++;
	check_endline(line, x, y, data);
}
