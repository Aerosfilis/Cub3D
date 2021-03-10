/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:22:55 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/10 13:28:52 by cbugnon          ###   ########.fr       */
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
	while (x < data->smap.x - 1)
	{
		y = 1;
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

void			check_doublon(char *line, t_data *data, int ismap)
{
	static unsigned char	check = 0;
	unsigned char			flag;

	flag = (line[0] == 'N') + 2 * (line[0] == 'S' && line[1] == 'O') + 3
		* (line[0] == 'W') + 4 * (line[0] == 'E') + 5 * (line[0] == 'S'
		&& line[1] == ' ') + 6 * (line[0] == 'F') + 7 * (line[0] == 'C');
	if (flag == 0 && line[0] != 'R')
		return ;
	if ((ismap && check != 0xFF) || ((1 << flag) & check))
	{
		free(line);
		ft_error(EINVSET, data);
	}
	check |= 1 << flag;
}
