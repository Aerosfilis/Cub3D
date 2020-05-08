/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:44:44 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 18:16:43 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

const void		(*g_set_data[8])(char *, t_data *) =
{
	set_data_res,
	set_data_tex,
	set_data_col,
	set_data_map
};

static void		init_map(t_data *data, int fd)
{
	char	*line;
	int		ismap;

	ismap = 0;
	while (gnl(fd, &line, data) >= 0)
	{
		if (get_function(line) != 3 && ismap)
			ft_error(EINVMAP, data);
		ismap = get_function(line) == 3 ? 1 : ismap;
		data->smap.y += ismap;
		data->smap.x = get_function(line) != 3 || data->smap.x >
			ft_strlen(line) ? data->smap.x : ft_strlen(line);
		free(line);
	}
	free(line);
	set_map(data);
}

void			parse(const char *pathname, t_data *data)
{
	char	*line;

	if ((data->mapfd = open(pathname, O_RDONLY)) < 0)
		ft_error(errno, data);
	if (data->map)
		free_datamap(data);
	init_map(data, data->mapfd);
	close(data->mapfd);
	data->mapfd = 0;
	if ((data->mapfd = open(pathname, O_RDONLY)) < 0)
		ft_error(errno, data);
	while (gnl(data->mapfd, &line, data) >= 0)
	{
		if (get_function(line) >= 0)
			(g_set_data[get_function(line)])(line, data);
		free(line);
	}
	free(line);
	close(data->mapfd);
}

void			set_data_res(char *line, t_data *data)
{
	size_t		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	data->res.x = stoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	data->res.y = stoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (line[i] || data->res.x < 1 || data->res.y < 1)
	{
		free(line);
		ft_error(EINVSET, data);
	}
}

static int		check_path(char *path, t_data *data)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) >= 0)
		close(fd);
	return (fd);
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
	if (!(data->path_tex[i] = malloc(sizeof(char) * ft_strlen(line + j))))
	{
		free(line);
		ft_error(errno, data);
	}
	k = -1;
	while (line[j + (++k)])
		data->path_tex[i][k] = line[j + k];
	data->path_tex[i][k] = 0;
	if (check_path(data->path_tex[i], data) < 0)
	{
		free(line);
		ft_error(EINVSET, data);
	}
}
