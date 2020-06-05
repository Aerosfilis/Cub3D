/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:55:26 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/05 16:34:45 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "struct.h"
#include "mlx.h"

void			mlx_null(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
}

void			new_mlx(t_mlx *mlx, char *prog_name, t_data *data)
{
	if (!(mlx->ptr = mlx_init()) || !(mlx->win = mlx_new_window(mlx->ptr,
			data->res.x, data->res.y, prog_name)))
		ft_error(EMLX, data);
}

void			free_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->ptr, mlx->win);
	if (mlx->ptr)
		free(mlx->ptr);
	mlx_null(mlx);
}

void			new_pos(t_pos *pos, ssize_t x, ssize_t y)
{
	pos->x = x;
	pos->y = y;
}
