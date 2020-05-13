/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 17:48:02 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/13 18:47:50 by cbugnon          ###   ########.fr       */
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
