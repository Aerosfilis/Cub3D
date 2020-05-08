/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:48:02 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 18:21:35 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"

static int		nextrgb(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	return (i + (line[i] == ','));
}

void			set_data_col(char *line, t_data *data)
{
	size_t	i;
	int		rgb[3];

	i = 1;
	while (line[i] == ' ')
		i++;
	rgb[0] = stoi(line + i);
	i += nextrgb(line + i);
	rgb[1] = stoi(line + i);
	i += nextrgb(line + i);
	rgb[2] = stoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[0] == 'C')
		data->col_ceil = rgbtoi(rgb);
	else if (line[0] == 'F')
		data->col_floor = rgbtoi(rgb);
	if (line[i] || data->col_ceil < 0 || data->col_floor < 0)
	{
		free(line);
		ft_error(EINVSET, data);
	}
}

void			set_data_map(char *line, t_data *data)
{
	static ssize_t	idx = 0;
	static int		isstartset = 0;
	ssize_t			i;

	i = -1;
	while (line[++i])
		if (line[i] != ' ')
		{
			if (line[i] >= '0' && line[i] <= '2' && ((idx > 0
					&& idx < data->smap.y && i > 0 && i < data->smap.x)
					|| line[i] == '1'))
				data->map[i][idx] = line[i] - 48;
			else if (!isstartset && (line[i] == 'N' || line[i] == 'S' || line[i]
					== 'W' || line[i] == 'E') && ((idx > 0 && idx < data->smap.y
					&& i > 0 && i < data->smap.x) || line[i] == '1'))
				data->map[i][idx] = 3 + (line[i] == 'S')
					+ 2 * (line[i] == 'W') + 3 * (line[i] == 'E');
			else
			{
				free(line);
				ft_error(EINVMAP, data);
			}
		}
	idx++;
}
