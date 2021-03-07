/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:22:55 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/05 12:11:38 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"
#include "parse.h"
#include <sys/types.h>

static int		find_checkstart(char *line, t_data *data)
{
	int		x;
	char	cell;

	x = data->smap.x - 1;
	cell = data->map[x][0];
	while (x > 0 && cell == MAPEMPTY)
	{
		if (cell != MAPWALL && cell != MAPEMPTY)
		{
			free(line);
			ft_error(EINVMAP, data);
		}
		cell = data->map[x][0];
		x--;
	}
	return (x);
}

static void		check_endline(char *line, int x, int y, t_data *data)
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
	int		x;
	int		y;

	x = find_checkstart(line, data);
	y = 0;
	while (y < data->smap.y - 1)
	{
		while (x < data->smap.x - 1 && data->map[x][y] == MAPWALL)
			x++;
		check_endline(line, x, y, data);
		x -= data->map[x][y] != MAPWALL ? 1 : 0;
		while (x > 0 && data->map[x][y] == MAPWALL
				&& data->map[x][y + 1] == MAPEMPTY)
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
