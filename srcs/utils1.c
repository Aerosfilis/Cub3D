/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:35:27 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/07 16:52:13 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <stdio.h>

const char		*g_errlst[] =
{
	"\n",
	"String pointer null\n",
	"Passed Null pointer\n",
	"Invalid settings\n",
	"Invalid map\n"
};

ssize_t			str_append(char **s1, const char *s2, ssize_t len, t_data *data)
{
	size_t		i;
	size_t		j;
	char		*res;

	if (!s1 || !(*s1) || !s2)
		ft_error(ESPNULL, data);
	if (!(res = malloc(sizeof(char) * (ft_strlen(*s1)
						+ (len < 0 ? ft_strlen(s2) : len) + 1))))
		ft_error(errno, data);
	i = -1;
	while ((*s1)[++i])
		res[i] = (*s1)[i];
	j = 0;
	while (len < 0 ? s2[j] : j < len)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = 0;
	free(*s1);
	*s1 = res;
	return (i + j);
}

void			ft_error(int err, t_data *data)
{
	errno = err;
	if (!data || !data->err_msg)
	{
		write(2, "ERROR\n", 6);
		if (err >= 0)
			perror("");
		else
			write(2, g_errlst[-err], ft_strlen(g_errlst[-err]));
	}
	else if (err >= 0)
		perror(data->err_msg);
	else
	{
		write(2, data->err_msg, ft_strlen(data->err_msg));
		write(2, g_errlst[-err], ft_strlen(g_errlst[-err]));
	}
	if (data)
		free_data(data);
	exit(EXIT_FAILURE);
}
