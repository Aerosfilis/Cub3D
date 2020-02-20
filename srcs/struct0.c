/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:37:51 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 13:57:03 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "utils.h"

void			new_data(t_data *data, char *prog_name)
{
	if (!data)
		ft_error(ENULLPTR, NULL); 
	if (!(data = malloc(sizeof(t_data))))
		ft_error(errno, NULL);
	new_pos(&(data->res), 0, 0);
	new_pos(&(data->map_size, 0, 0);
	data->map = NULL;
	data->path_NO = NULL;
	data->path_SO = NULL;
	data->path_WE = NULL;
	data->path_EA = NULL;
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
