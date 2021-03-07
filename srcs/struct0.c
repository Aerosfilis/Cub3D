/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:37:51 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 16:30:56 by cbugnon          ###   ########.fr       */
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
	new_pos(&(data->smap), -1, -1);
	new_pos(&(data->res), -1, -1);
	data->map = NULL;
	data->mapfd = 0;
	i = -1;
	while (++i < NB_TEXTURE)
		data->path_tex[i] = NULL;
	data->err_msg = maybemalloc(sizeof(char), data);
	data->err_msg[0] = 0;
	str_append(&(data->err_msg), "Error\n", -1, data);
	str_append(&(data->err_msg), prog_name, -1, data);
	data->map = maybemalloc(sizeof(char *), data);
	data->map[0] = 0;
	data->sprites = NULL;
	data->nb_sprites = 0;
	mlx_null(data);
}

void			set_map(t_data *data)
{
	t_pos		pos;

	data->map = maybemalloc(sizeof(char *) * data->smap.x, data);
	pos.x = -1;
	while (++pos.x < data->smap.x)
		data->map[pos.x] = NULL;
	pos.x = -1;
	while (++pos.x < data->smap.x)
	{
		data->map[pos.x] = maybemalloc(sizeof(char) * data->smap.y, data);
		pos.y = -1;
		while (++pos.y < data->smap.y)
			data->map[pos.x][pos.y] = MAPSPACE;
	}
}

void			free_datamap(t_data *data)
{
	int		i;

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
	free_mlx(data);
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
	free_mlx(data);
	if (data->mapfd > 0)
		close(data->mapfd);
	if (data->sprites)
		free(data->sprites);
	data->mapfd = 0;
}
