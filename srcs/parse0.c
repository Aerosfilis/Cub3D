/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:44:44 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/07 16:26:31 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

const void		(*g_set_data[8])(const char *, t_data *) =
{
	set_data_res,
	set_data_tex,
	set_data_col,
	set_data_map
};

static int		get_function(const char *l)
{
	if (l[0] == 'R' && l[1] == ' ')
		return (0);
	else if ((l[0] == 'N' && l[1] == 'O' && l[2] == ' ')
			|| (l[0] == 'S' && l[1] == 'O' && l[2] == ' ')
			|| (l[0] == 'W' && l[1] == 'E' && l[2] == ' ')
			|| (l[0] == 'E' && l[1] == 'A' && l[2] == ' ')
			|| (l[0] == 'S' && l[1] == ' '))
		return (1);
	else if ((l[0] == 'F' || l[0] == 'C') && l[1] == ' ')
		return (2);
	else if (l[0] == 0)
		return (-1);
	else
		return (3);
}

#include <stdio.h>
static ssize_t	gnl(const int fd, char **line, t_data *data)
{
	static char		buf[BUFSIZE];
	static size_t	idx = 0;
	static ssize_t	nb_b = 0;
	size_t			i;

	if (!(*line = malloc(sizeof(char))) ||
			(!nb_b && (nb_b = read(fd, buf, BUFSIZE)) < 0))
		ft_error(errno, data);
	if (!((*line)[0] = 0) && !(i = 0) && !nb_b)
		return (-1);
	while (!i)
	{
		while (buf[idx + i] && buf[idx + i] != '\n' && idx + i < nb_b)
			i++;
		str_append(line, buf + idx, i, data);
		idx += i + 1;
		if (idx >= nb_b)
		{
			if (!(i = 0) && !(idx = 0) && (nb_b = read(fd, buf, BUFSIZE)) < 0)
				ft_error(errno, data);
			else if (!nb_b)
				return (ft_strlen(*line));
		}
	}
	return (ft_strlen(*line));
}

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
		data->smap.x = data->smap.x > ft_strlen(line) ?
			data->smap.x : ft_strlen(line);
		free(line);
	}
	set_map(data);
}

void			parse(const char *pathname, t_data *data)
{
	int		fd;
	char	*line;

	if ((fd = open(pathname, O_RDONLY)) < 0)
		ft_error(errno, data);
	if (data->map)
		free_datamap(data);
	init_map(data, fd);
	close(fd);
	if ((fd = open(pathname, O_RDONLY)) < 0)
	   ft_error(errno, data);	
	while (gnl(fd, &line, data) >= 0)
	{
		if (get_function(line) >= 0)
			(g_set_data[get_function(line)])(line, data);
		free(line);
	}
	close(fd);
}

#include <stdio.h>
void			set_data_res(const char *line, t_data *data)
{
	printf("set data res\n");
}
void			set_data_tex(const char *line, t_data *data)
{
	printf("set data tex\n");
}
void			set_data_col(const char *line, t_data *data)
{
	printf("set data col\n");
}
void			set_data_map(const char *line, t_data *data)
{
	printf("set data map\n");
}
