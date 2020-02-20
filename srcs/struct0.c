/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:37:51 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 14:21:36 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"

void			new_data(t_data *data, char *prog_name)
{
	int			i;

	if (!data)
		ft_error(ENULLPTR, NULL); 
	if (!(data = malloc(sizeof(t_data))))
		ft_error(errno, NULL);
	new_pos(&(data->res), 0, 0);
	new_pos(&(data->map_size, 0, 0);
	data->map = NULL;
	i = -1;
	while (++i < NB_TEXTURE)
		data->path_texture[i] = NULL;
	new_mlx(&(data->mlx));
	if (!(data->err_msg = malloc(sizeof(char))))
		ft_error(errno, data);
	data->err_msg[0] = 0;
	str_append(&(data->err_msg), "ERROR\n", 0, data);
	str_append(&(data->err_msg), prog_name, 0, data);
	if (!(data->map = malloc(sizeof(unsigned char *))))
		ft_error(errno, data);
	data->map[0] = 0;
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
	int		i;

	if (!data)
		return ;
	if (data->map)
		free_datamap(data->map);
	i = -1;
	while (i < NB_TEXTURE)
		if (data->path_texture[i])
			free(data->path_texture[i]);
	if (data->err_msg)
		free(data->err_msg);
	free_mlx(data->mlx);
	free(data);
}

void			new_pos(t_pos *pos, ssize_t x, ssize_t y)
{
	pos->x = 0;
	pos->y = 0;
}
