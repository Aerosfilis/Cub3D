/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:42:11 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/24 10:27:50 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include "event.h"
#include "render.h"
#include "struct.h"

#include <stdio.h>
int		key_press(int key, t_mlx *mlx)
{	
	printf("keypress: %d\n", key);
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->kpr[key] = 1;
	mlx->kpr[KS] += (key == KW && mlx->kpr[KS] == 1);
	mlx->kpr[KW] += (key == KS && mlx->kpr[KW] == 1);
	mlx->kpr[KD] += (key == KA && mlx->kpr[KD] == 1);
	mlx->kpr[KA] += (key == KD && mlx->kpr[KA] == 1);
	return (0);
}

int		key_release(int key, t_mlx *mlx)
{
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->kpr[key] = 0;
	mlx->kpr[KS] -= (key == KW && mlx->kpr[KS] == 2);
	mlx->kpr[KW] -= (key == KS && mlx->kpr[KW] == 2);
	mlx->kpr[KD] -= (key == KA && mlx->kpr[KD] == 2);
	mlx->kpr[KA] -= (key == KD && mlx->kpr[KA] == 2);
	return (0);
}

void	update_pos(t_mlx *mlx, t_data *data)
{
	mlx->x += (((mlx->kpr[KW] == 1) - (mlx->kpr[KS] == 1)) * MOVSPD * mlx->ox +
		((mlx->kpr[KA] == 1) - (mlx->kpr[KD] == 1)) * MOVSPD * mlx->oy) *
		(mlx->kpr[SH] == 1 ? SPRINT : 1);
	mlx->y += (((mlx->kpr[KW] == 1) - (mlx->kpr[KS] == 1)) * MOVSPD * mlx->oy +
		((mlx->kpr[KD] == 1) - (mlx->kpr[KA] == 1)) * MOVSPD * mlx->ox) *
		(mlx->kpr[SH] == 1 ? SPRINT : 1);
	(void)data;
}

void	update_rot(t_mlx *mlx)
{
	double		tmp;

	if (mlx->kpr[AL] == 1)
	{
		tmp = mlx->ox * cos(-ROTSPD) - mlx->oy * sin(-ROTSPD);
		mlx->oy = mlx->ox * sin(-ROTSPD) + mlx->oy * cos(-ROTSPD);
		mlx->ox = tmp;
	}
	else if (mlx->kpr[AR] == 1)
	{
		tmp = mlx->ox * cos(ROTSPD) - mlx->oy * sin(ROTSPD);
		mlx->oy = mlx->ox * sin(ROTSPD) + mlx->oy * cos(ROTSPD);
		mlx->ox = tmp;
	}
}

int		loop(t_data *data)
{
	update_pos(&data->mlx, data);
	update_rot(&data->mlx);
	cycle_angle(&data->mlx, data);
	return (0);
}
