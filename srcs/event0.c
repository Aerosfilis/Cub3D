/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:42:11 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/08 10:00:08 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include "mlx.h"
#include "event.h"
#include "struct.h"
#include "render.h"

static void		update_pos(t_data *data)
{
	data->x += (((data->kpr[KW] == 1) - (data->kpr[KS] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KA] == 1 || data->kpr[KD] == 1)) *
		data->ox + ((data->kpr[KA] == 1) - (data->kpr[KD] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KW] == 1 || data->kpr[KS] == 1)) *
		data->oy) * (data->kpr[SH] == 1 ? SPRINT : 1);
	data->x += (data->x < WRAP) * data->smap.x
		- (data->x >= data->smap.x - WRAP) * data->smap.x;
	data->y += (((data->kpr[KW] == 1) - (data->kpr[KS] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KD] == 1 || data->kpr[KA] == 1)) *
		data->oy + ((data->kpr[KD] == 1) - (data->kpr[KA] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KW] == 1 || data->kpr[KS] == 1)) *
		data->ox) * (data->kpr[SH] == 1 ? SPRINT : 1);
	data->y += (data->y < WRAP) * data->smap.y
		- (data->y >= data->smap.y - WRAP) * data->smap.y;
}

static void		update_rot(t_data *data)
{
	double		tmp;

	if (data->kpr[AL] == 1)
	{
		tmp = data->ox * cos(-ROTSPD) - data->oy * sin(-ROTSPD);
		data->oy = data->ox * sin(-ROTSPD) + data->oy * cos(-ROTSPD);
		data->ox = tmp;
	}
	else if (data->kpr[AR] == 1)
	{
		tmp = data->ox * cos(ROTSPD) - data->oy * sin(ROTSPD);
		data->oy = data->ox * sin(ROTSPD) + data->oy * cos(ROTSPD);
		data->ox = tmp;
	}
}

int				loop(t_data *data)
{
	update_pos(data);
	update_rot(data);
	if (data->x > 0 && data->x < (double)data->smap.x
			&& data->y > 0 && data->y < (double)data->smap.y
			&& data->map[(int)data->x][(int)data->y] != MAPWALL)
		cycle_angle(data);
	draw_sprites(data);
	mlx_put_image_to_window(data->ptr, data->win,
		data->scn.ptr, 0, 0);
	return (0);
}
