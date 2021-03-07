/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:48:02 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 18:48:10 by cbugnon          ###   ########.fr       */
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

int				set_tile(char tile)
{
	if (tile == ' ')
		return (MAPSPACE);
	if (tile == '1')
		return (MAPWALL);
	if (tile == '2')
		return (MAPSPRITE);
	if (tile == 'N')
		return (MAPNORTH);
	if (tile == 'S')
		return (MAPSOUTH);
	if (tile == 'E')
		return (MAPEAST);
	if (tile == 'W')
		return (MAPWEST);
	if (tile == '0')
		return (MAPEMPTY);
	return (-1);
}

void			set_data_map(char *line, t_data *data)
{
	static int	y = 0;
	int			x;
	static int	startset = 0;

	x = -1;
	while (line[++x])
	{
		data->map[x][y] = set_tile(line[x]);
		if (data->map[x][y] == MAPSPRITE)
			data->nb_sprites++;
		if (line[x] == 'N' || line[x] == 'S'
				|| line[x] == 'E' || line[x] == 'W')
			startset++;
		if (((x == 0 || x == data->smap.x - 1 || y == 0 || y ==
			data->smap.y - 1 || !line[x + 1]) && data->map[x][y] != MAPWALL
			&& data->map[x][y] != MAPSPACE) || startset > 1 || (y
			>= data->smap.y - 1 && startset != 1) || data->map[x][y] < 0)
		{
			free(line);
			ft_error(EINVMAP, data);
		}
	}
	y++;
	if (y >= data->smap.y)
		check_enclosed(line, data);
}
