/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:37:51 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 14:52:05 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"
#include <unistd.h>

void			new_data(t_data *data, char *prog_name)
{
	int			i;

	if (!data)
		ft_error(ENULLPTR, NULL);
	new_pos(&(data->smap), 0, 0);
	new_pos(&(data->res), 0, 0);
	data->map = NULL;
	data->mapfd = 0;
	i = -1;
	while (++i < NB_TEXTURE)
		data->path_tex[i] = NULL;
	new_mlx(&(data->mlx));
	if (!(data->err_msg = malloc(sizeof(char))))
		ft_error(errno, data);
	data->err_msg[0] = 0;
	str_append(&(data->err_msg), "ERROR\n", -1, data);
	str_append(&(data->err_msg), prog_name, -1, data);
	if (!(data->map = malloc(sizeof(char *))))
		ft_error(errno, data);
	data->map[0] = 0;
}

static void		set_map(t_data *data)
{
	t_pos		pos;

	if (!(data->map = malloc(sizeof(char *) * data->smap.x)))
		ft_error(errno, data);
	pos.x = -1;
	while (++pos.x < data->smap.x)
		data->map[pos.x] = NULL;
	pos.x = -1;
	while (++pos.x < data->smap.x)
	{
		if (!(data->map[pos.x] = malloc(sizeof(char) * data->smap.y)))
			ft_error(errno, data);
		pos.y = -1;
		while (++pos.y < data->smap.y)
			data->map[pos.x][pos.y] = !pos.x || !pos.y || pos.x + 1 ==
				data->smap.x || pos.y + 1 == data->smap.y ? 1 : 0;
	}
}

void			init_map(t_data *data, int fd)
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

void			free_datamap(t_data *data)
{
	size_t		i;

	if (!data->map)
		return ;
	i = 0;
	while (i < data->smap.x)
	{
		if (data->map[i])
		{
			free(data->map[i]);
			data->map[i] = NULL;
		}
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void			free_data(t_data *data)
{
	int		i;

	if (!data)
		return ;
	if (data->map)
		free_datamap(data);
	i = -1;
	while (++i < NB_TEXTURE)
	{
		if (data->path_tex[i])
			free(data->path_tex[i]);
	}
	if (data->err_msg)
		free(data->err_msg);
	free_mlx(&(data->mlx));
	if (data->mapfd > 0)
		close(data->mapfd);
	data->mapfd = 0;
}
