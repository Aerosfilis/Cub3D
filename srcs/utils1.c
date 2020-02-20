/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:35:27 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 11:52:03 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

ssize_t			str_append(char **s1, const char *s2, size_t len, t_data *data)
{
	size_t		i;
	size_t		j;
	char		*res;

	if (!s1 || !(*s1) || !s2)
		ft_error(ESPNULL, data);
	if (!(res = malloc(sizeof(char) * (ft_strlen(*s1)
						+ (len == 0 ? ft_strlen(s2) : len) + 1))))
		ft_error(errno, data);
	i = -1;
	while ((*s1)[++i])
		res[i] = (*s1)[i];
	j = 0;
	while (len == 0 ? s2[j] : j < len)
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
	if (!data || !(data->err_msg))
	{
		errno = err;
		perror("ERROR\n");
	}
	else if (err >= 0)
	{
		errno = err;
		perror(data->err_msg);
	}
	else
	{
		if (!(str = malloc(sizeof(char))))
			ft_error(errno, data);
		str[0] = 0;
		str_append(&(data->msg), g_errlst[-err], 0, data);
		write(2, str, ft_strlen(data->msg));
	}
	if (data)
		free_data(data);
	exit(EXIT_FAILURE);
}

t_data			*new_data(char *prog_name)
{
	t_data	*data;

	if (!(data = malloc(sizeof(t_data))))
		ft_error(errno, NULL);
	data->res_x = 0;
	data->res_y = 0;
	data->map_x = 0;
	data->map_y = 0;
	data->map = NULL;
	data->path_NO = NULL;
	data->path_SO = NULL;
	data->path_WE = NULL;
	data->path_EA = NULL;
	data->color_ceil = 0;
	data->color_floor = 0;
	data->mlx = NULL;
	if (!(res = malloc(sizeof(char) * (ft_strlen(prog_name) + ))))
		ft_error(errno, data);
	str_append(&(data->err_msg), "ERROR\n", 0, data);
	str_append(&(data->err_msg), prog_name, 0, data);
	if (!(data->map = malloc(sizeof(unsigned char *))))
		ft_error(errno, data);
	data->map[0] = 0;
	return (data);
}

static void		free_datamap(unsigned char **map)
{
	size_t		i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void			free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map)
		free_datamap(data->map);
	if (data->path_NO)
		free(data->path_NO);
	if (data->path_SO)
		free(data->path_SO);
	if (data->path_WE)
		free(data->path_WE);
	if (data->path_EA)
		free(data->path_EA);
	if (data->mlx)
		free_mlx(data->mlx);
	free(data);
}
