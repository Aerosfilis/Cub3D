/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:55:26 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 13:21:22 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "struct.h"

void			new_mlx(t_mlx *mlx)
{
	mlx->ptr = NULL;
	mlx->win = NULL;
}

void			free_mlx(t_mlx *mlx)
{
	(void)mlx;
}

void			new_pos(t_pos *pos, ssize_t x, ssize_t y)
{
	pos->x = x;
	pos->y = y;
}
