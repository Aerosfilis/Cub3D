/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:55:26 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/05 22:35:38 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "struct.h"
#include "mlx.h"

void			mlx_null(t_mlx *mlx)
{
	size_t		i;

	mlx->ptr = NULL;
	mlx->win = NULL;
	i = -1;
	while (++i < USHRT_MAX)
		mlx->kpr[i] = 0;
	new_pos(&(mlx->chr), 0, 0);
	new_pos(&(mlx->ori), 0, 0);
	i = -1;
	while (++i < NB_TEXTURE)
	{
		mlx->tex[i] = NULL;
		new_pos(&(mlx->tres[i]), 0, 0);
	}
	mlx->scn = NULL;
}

void			set_start(t_mlx *mlx, t_data *data)
{
	size_t		x;
	size_t		y;

	x = -1;
	while (++x < data->smap.x)
	{
		y = -1;
		while (++y < data->smap.y)
		{
			if (data->map[x][y] >= MAPNORTH && data->map[x][y] <= MAPWEST)
			{
				mlx->chr.x = x * UNIT + UNIT / 2;
				mlx->chr.y = y * UNIT + UNIT / 2;
				mlx->ori.x = (data->map[x][y] == MAPEAST)
						- (data->map[x][y] == MAPWEST);
				mlx->ori.y = (data->map[x][y] == MAPSOUTH)
						- (data->map[x][y] == MAPNORTH);
				return ;
			}
		}
	}
}

void			new_mlx(t_mlx *mlx, char *prog_name, t_data *data)
{
	size_t		i;
	int			width;
	int			height;

	if (!(mlx->ptr = mlx_init()) || !(mlx->win = mlx_new_window(mlx->ptr,
			data->res.x, data->res.y, prog_name)))
		ft_error(EMLX, data);
	set_start(mlx, data);
	i = -1;
	while (++i < NB_TEXTURE)
	{
		if (!(mlx->tex[i] = mlx_xpm_file_to_image(mlx->ptr, data->path_tex[i],
				&width, &height)))
			ft_error(ETEXTURE, data);
		mlx->tres[i].x = (size_t)width;
		mlx->tres[i].y = (size_t)height;
	}
}

void			free_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		free(mlx->ptr);
	mlx_null(mlx);
}

void			new_pos(t_pos *pos, size_t x, size_t y)
{
	pos->x = x;
	pos->y = y;
}
