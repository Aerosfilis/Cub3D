/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:55:26 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/22 17:14:42 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
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
	mlx->z = 0;
	i = -1;
	while (++i < NB_TEXTURE)
		img_null(&(mlx->tex[i]));
	img_null(&mlx->scn);
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
				mlx->x = (double)x + 0.5;
				mlx->y = (double)y + 0.5;
				mlx->ox = (data->map[x][y] == MAPEAST)
						- (data->map[x][y] == MAPWEST);
				mlx->oy = (data->map[x][y] == MAPSOUTH)
						- (data->map[x][y] == MAPNORTH);
				return ;
			}
		}
	}
}

void			new_mlx(t_mlx *mlx, char *prog_name, t_data *data)
{
	size_t		i;

	if (!(mlx->ptr = mlx_init()))
		ft_error(EMLX, data);
	if (!(mlx->win = mlx_new_window(mlx->ptr, data->res.x,
					data->res.y, prog_name)))
		ft_error(EMLX, data);
	set_start(mlx, data);
	i = -1;
	while (++i < NB_TEXTURE)
		new_tex(i, &(mlx->tex[i]), data);
	new_img(&mlx->scn, (int)data->res.x, (int)data->res.y, data);
}

void			free_mlx(t_mlx *mlx)
{
	int		i;

	i = -1;
	while (++i < NB_TEXTURE)
		free_img(&mlx->tex[i], mlx);
	free_img(&mlx->scn, mlx);
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
