/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:22:55 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 12:47:31 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"
#include "parse.h"
#include <sys/types.h>

void			check_enclosed(char *line, t_data *data)
{
	int		x;
	int		y;

	x = 1;
	y = 1;
	while (x < data->smap.x - 1)
	{
		while (y < data->smap.y - 1)
		{
			if (data->map[x][y] != MAPWALL && data->map[x][y] != MAPSPACE
					&& (data->map[x + 1][y] == MAPSPACE || data->map[x - 1][y]
					== MAPSPACE || data->map[x][y + 1] == MAPSPACE
					|| data->map[x][y - 1] == MAPSPACE))
			{
				free(line);
				ft_error(EINVMAP, data);
			}
			y++;
		}
		x++;
	}
}
