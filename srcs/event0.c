/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:42:11 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/27 17:23:35 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include "mlx.h"
#include "event.h"
#include "render.h"
#include "struct.h"

#include <stdio.h>
int				key_press(int key, t_data *data)
{	
	t_mlx	*mlx;

	printf("keypress: %d\n", key);
	mlx = &data->mlx;
	if (key == ES)
		quit_cubed(data);
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->kpr[key] = 1;
	mlx->kpr[KS] += (key == KW && mlx->kpr[KS] == 1);
	mlx->kpr[KW] += (key == KS && mlx->kpr[KW] == 1);
	mlx->kpr[KD] += (key == KA && mlx->kpr[KD] == 1);
	mlx->kpr[KA] += (key == KD && mlx->kpr[KA] == 1);
	mlx->kpr[AL] += (key == AR && mlx->kpr[AL] == 1);
	mlx->kpr[AR] += (key == AL && mlx->kpr[AR] == 1);
	return (0);
}

int				key_release(int key, t_data *data)
{
	t_mlx	*mlx;

	mlx = &data->mlx;
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->kpr[key] = 0;
	mlx->kpr[KS] -= (key == KW && mlx->kpr[KS] == 2);
	mlx->kpr[KW] -= (key == KS && mlx->kpr[KW] == 2);
	mlx->kpr[KD] -= (key == KA && mlx->kpr[KD] == 2);
	mlx->kpr[KA] -= (key == KD && mlx->kpr[KA] == 2);
	mlx->kpr[AL] -= (key == AR && mlx->kpr[AL] == 2);
	mlx->kpr[AR] -= (key == AL && mlx->kpr[AR] == 2);
	return (0);
}

static double	wallcolision(int axis, t_mlx *mlx, t_data *data)
{
	if (mlx->x > COLISIZE && mlx->x + COLISIZE < (double)data->smap.x
		&& mlx->y > COLISIZE && mlx->y + COLISIZE < (double)data->smap.y)
	{
		if (data->map[(int)(mlx->x - COLISIZE * axis)]
				[(int)(mlx->y - COLISIZE * (!axis))] == MAPWALL)
			return (axis ? floor(mlx->x - COLISIZE) + COLISIZE + 1
					: floor(mlx->y - COLISIZE) + COLISIZE + 1);
		if (data->map[(int)(mlx->x + COLISIZE * axis)]
				[(int)(mlx->y + COLISIZE * (!axis))] == MAPWALL)
			return (axis ? floor(mlx->x + COLISIZE) - COLISIZE
					: floor(mlx->y + COLISIZE) - COLISIZE);
	}
	return (axis ? mlx->x : mlx->y);
}


void			update_pos(t_mlx *mlx, t_data *data)
{
	mlx->x += (((mlx->kpr[KW] == 1) - (mlx->kpr[KS] == 1)) * MOVSPD *
		(1 - 0.3 * (mlx->kpr[KA] == 1 || mlx->kpr[KD] == 1))*
		mlx->ox + ((mlx->kpr[KA] == 1) - (mlx->kpr[KD] == 1)) * MOVSPD *
		(1 - 0.3 * (mlx->kpr[KW] == 1 || mlx->kpr[KS] == 1))*
		mlx->oy) * (mlx->kpr[SH] == 1 ? SPRINT : 1);
	mlx->x = wallcolision(1, mlx, data);
	mlx->y += (((mlx->kpr[KW] == 1) - (mlx->kpr[KS] == 1)) * MOVSPD *
		(1 - 0.3 * (mlx->kpr[KD] == 1 || mlx->kpr[KA] == 1))*
		mlx->oy + ((mlx->kpr[KD] == 1) - (mlx->kpr[KA] == 1)) * MOVSPD *
		(1 - 0.3 * (mlx->kpr[KW] == 1 || mlx->kpr[KS] == 1))*
		mlx->ox) * (mlx->kpr[SH] == 1 ? SPRINT : 1);
	mlx->y = wallcolision(0, mlx, data);
}

void			update_rot(t_mlx *mlx)
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

int				quit_cubed(t_data *data)
{
	if (data)
		free_data(data);
	exit(EXIT_SUCCESS);
}

int				loop(t_data *data)
{
	update_pos(&data->mlx, data);
	update_rot(&data->mlx);
	cycle_angle(&data->mlx, data);
	mlx_put_image_to_window(data->mlx.ptr, data->mlx.win, data->mlx.scn.ptr, 0, 0);
	return (0);
}
