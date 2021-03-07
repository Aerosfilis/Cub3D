/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 13:49:23 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 15:03:04 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

static int		readnext(const int fd, char *buf, char **line, t_data *data)
{
	int	res;

	if ((res = read(fd, buf, BUFSIZE - 1)) < 0)
	{
		free(*line);
		ft_error(errno, data);
	}
	return (res);
}

int				gnl(const int fd, char **line, t_data *data)
{
	static char		buf[BUFSIZE];
	static int		idx = 0;
	static int		nb_b = 0;
	size_t			i;

	if ((!nb_b && (nb_b = read(fd, buf, BUFSIZE - 1)) < 0))
		ft_error(errno, data);
	(*line) = maybemalloc(sizeof(char), data);
	(*line)[0] = 0;
	if (!nb_b)
		return (-1);
	i = 0;
	while (!i)
	{
		while (buf[idx + i] && buf[idx + i] != '\n' && idx + i < (size_t)nb_b)
			i++;
		str_append(line, buf + idx, i, data);
		idx = idx + i + 1 >= (size_t)nb_b ? 0 : idx + i + 1;
		i = !idx ? 0 : i;
		i = !i && !idx ? i : 1;
		if (!idx && !(nb_b = readnext(fd, buf, line, data)))
			return (ft_strlen(*line));
	}
	return (ft_strlen(*line));
}

int				get_function(const char *l)
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

inline int		rgbtoi(int rgb[3])
{
	int	r;
	int	g;
	int	b;

	r = rgb[0];
	g = rgb[1];
	b = rgb[2];
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) + (g << 8) + b);
}

double			mod(double n, double m)
{
	while (n < 0)
		n += m;
	while (n >= m)
		n -= m;
	return (n);
}
