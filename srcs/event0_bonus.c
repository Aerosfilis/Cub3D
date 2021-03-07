/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event0_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:42:11 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 15:09:56 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include "mlx.h"
#include "event_bonus.h"
#include "struct.h"
#include "render_bonus.h"

static double	wallcolision(int axis, t_data *data)
{
	if (data->x > COLISIZE && data->x + COLISIZE < (double)data->smap.x
		&& data->y > COLISIZE && data->y + COLISIZE < (double)data->smap.y)
	{
		if (data->map[(int)(data->x - COLISIZE * axis)]
				[(int)(data->y - COLISIZE * (!axis))] == MAPWALL ||
				data->map[(int)(data->x - COLISIZE * axis)]
				[(int)(data->y - COLISIZE * (!axis))] == MAPSPRITE)
		{
			return (axis ? floor(data->x - COLISIZE) + COLISIZE + 1 :
					floor(data->y - COLISIZE) + COLISIZE + 1);
		}
		if (data->map[(int)(data->x + COLISIZE * axis)]
				[(int)(data->y + COLISIZE * (!axis))] == MAPWALL ||
				data->map[(int)(data->x + COLISIZE * axis)]
				[(int)(data->y + COLISIZE * (!axis))] == MAPSPRITE)
			return (axis ? floor(data->x + COLISIZE) - COLISIZE :
					floor(data->y + COLISIZE) - COLISIZE);
	}
	return (axis ? data->x : data->y);
}

static void		update_pos(t_data *data)
{
	data->x += (((data->kpr[KW] == 1) - (data->kpr[KS] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KA] == 1 || data->kpr[KD] == 1)) *
		data->ox + ((data->kpr[KA] == 1) - (data->kpr[KD] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KW] == 1 || data->kpr[KS] == 1)) *
		data->oy) * (data->kpr[SH] == 1 ? SPRINT : 1);
	data->x = wallcolision(1, data);
	data->y += (((data->kpr[KW] == 1) - (data->kpr[KS] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KD] == 1 || data->kpr[KA] == 1)) *
		data->oy + ((data->kpr[KD] == 1) - (data->kpr[KA] == 1)) * MOVSPD *
		(1 - 0.3 * (data->kpr[KW] == 1 || data->kpr[KS] == 1)) *
		data->ox) * (data->kpr[SH] == 1 ? SPRINT : 1);
	data->y = wallcolision(0, data);
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
	cycle_angle(data);
	draw_sprites(data);
	mlx_put_image_to_window(data->ptr, data->win,
		data->scn.ptr, 0, 0);
	return (0);
}
