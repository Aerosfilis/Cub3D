/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:48:02 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/26 00:16:32 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

static int		check_path(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) >= 0)
		close(fd);
	return (fd);
}

static int		pathlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && str[i - 1] == ' ')
		i--;
	return (i);
}

void			set_data_tex(char *line, t_data *data)
{
	int		i;
	int		j;
	int		k;

	i = (line[0] == 'N') + 2 * (line[0] == 'S' && line[1] == 'O') + 3 *
		(line[0] == 'W') + 4 * (line[0] == 'E');
	j = 2 + (i > 0);
	while (line[j] == ' ')
		j++;
	if (!(data->path_tex[i] = malloc(sizeof(char) * (pathlen(line + j) + 1))))
	{
		free(line);
		ft_error(errno, data);
	}
	k = -1;
	while (++k < pathlen(line + j))
		data->path_tex[i][k] = line[j + k];
	data->path_tex[i][k] = 0;
	if (check_path(data->path_tex[i]) < 0)
	{
		free(line);
		ft_error(EINVSET, data);
	}
}

void			set_data_map(char *line, t_data *data)
{
	static ssize_t	y = 0;
	ssize_t			x;
	static int		startset = 0;

	x = -1;
	while (line[++x])
	{
		data->map[x][y] = MAPWALL * (line[x] == '1' || line[x] == ' ') +
			MAPSPRITE * (line[x] == '2') + MAPNORTH * (line[x] == 'N') +
			MAPSOUTH * (line[x] == 'S') + MAPEAST * (line[x] == 'E') +
			MAPWEST * (line[x] == 'W');
		startset += (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
			|| line[x] == 'W');
		if (((x == 0 || x == data->smap.x - 1 || y == 0 || y ==
			data->smap.y - 1 || !line[x + 1]) && data->map[x][y] != MAPWALL)
			|| startset > 1 || (y >= data->smap.y - 1 && startset != 1))
		{
			free(line);
			ft_error(EINVMAP, data);
		}
	}
	y++;
	if (y >= data->smap.y)
		check_enclosed(line, data);
}
