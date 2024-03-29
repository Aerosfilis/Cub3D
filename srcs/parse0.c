/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:44:44 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 18:42:50 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

void			(*g_set_data[8])(char *, t_data *) =
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
		{
			free(line);
			ft_error(EINVMAP, data);
		}
		ismap = get_function(line) == 3 ? 1 : ismap;
		data->smap.y += ismap;
		data->smap.x = get_function(line) != 3 || data->smap.x >
			ft_strlen(line) ? data->smap.x : ft_strlen(line);
		check_doublon(line, data, ismap);
		free(line);
	}
	free(line);
	if (data->smap.x < 3 || data->smap.y < 3)
		ft_error(EINVMAP, data);
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
	if (data->res.x < 0 || data->res.y < 0 || data->col_ceil < 0
			|| data->col_floor < 0)
		ft_error(EINVSET, data);
}

void			set_data_res(char *line, t_data *data)
{
	size_t		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	data->res.x = (stoi(line + i) >= 0) ? stoi(line + i) : 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	data->res.y = stoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i] || data->res.x < 1 || data->res.y < 1)
	{
		free(line);
		ft_error(EINVSET, data);
	}
}

static int		nextrgb(char *line, size_t off, t_data *data)
{
	size_t	i;

	i = off;
	if (line[i] < '0' || line[i] > '9')
		return (0);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[i++] != ',')
	{
		free(line);
		ft_error(EINVSET, data);
	}
	while (line[i] == ' ')
		i++;
	if (line[i] < '0' || line[i] > '9')
	{
		free(line);
		ft_error(EINVSET, data);
	}
	return (i - off);
}

void			set_data_col(char *line, t_data *data)
{
	size_t	i;
	int		rgb[3];

	i = 1;
	while (line[i] == ' ')
		i++;
	rgb[0] = stoi(line + i);
	i += nextrgb(line, i, data);
	rgb[1] = stoi(line + i);
	i += nextrgb(line, i, data);
	rgb[2] = stoi(line + i);
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	while (line[i] == ' ')
		i++;
	if (line[0] == 'C')
		data->col_ceil = rgbtoi(rgb);
	else if (line[0] == 'F')
		data->col_floor = rgbtoi(rgb);
	if (line[i] || (line[0] == 'C' && data->col_ceil < 0)
			|| (line[0] == 'F' && data->col_floor < 0))
	{
		free(line);
		ft_error(EINVSET, data);
	}
}
