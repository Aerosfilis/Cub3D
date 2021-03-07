/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:08:25 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 11:16:52 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <math.h>
#include "render.h"
#include "utils.h"
#include "mlx.h"
#include "struct.h"

t_img			*get_texture(t_wall wall, t_data *data)
{
	if (!wall.side && data->y >= wall.y)
		return (&data->tex[TEX_NO]);
	else if (wall.side && data->x <= wall.x)
		return (&data->tex[TEX_EA]);
	else if (!wall.side)
		return (&data->tex[TEX_SO]);
	else
		return (&data->tex[TEX_WE]);
}

double			wall_h(int option, t_vrdr rdr, t_data *data)
{
	return ((0.25 + CROUCH * (option && data->kpr[CT] == 1)
		- CROUCH * (!option && data->kpr[CT] == 1))
		* (double)data->res.x / rdr.dist / tan(FOV / 360 * M_PI));
}

unsigned int	get_pixel(t_vrdr rdr, t_img *tex, t_wall wall, t_data *data)
{
	int		pixel;
	double	wall_h1;
	int		rgb[3];

	wall_h1 = wall_h(1, rdr, data);
	if (wall.side)
		pixel = (int)((wall.x > data->x ? wall.y - floor(wall.y) :
				floor(wall.y) - wall.y + 1) * tex->x);
	else
		pixel = (int)((wall.y < data->y ? wall.x - floor(wall.x) :
				floor(wall.x) - wall.x + 1) * tex->x);
	pixel = pixel * tex->bpp / 8 + (int)(((double)rdr.y -
			(double)data->res.y / 2 + wall_h1) /
			(wall_h(0, rdr, data) + wall_h1) * tex->y) * tex->sl;
	rgb[0] = (unsigned char)tex->addr[tex->endian != data->scn.endian ?
		pixel + 3 * tex->bpp / 32 : pixel + tex->bpp / 16] * tex->bpp / 32;
	rgb[1] = (unsigned char)tex->addr[tex->endian != data->scn.endian ?
		pixel + tex->bpp / 16 : pixel + tex->bpp / 32] * tex->bpp / 32;
	rgb[2] = (unsigned char)tex->addr[tex->endian != data->scn.endian ?
		pixel + tex->bpp / 32 : pixel] * tex->bpp / 32;
	return (rgbtoi(rgb));
}

void			draw_vertical(t_vrdr rdr, t_wall wall, t_data *data)
{
	t_img		*tex;

	tex = get_texture(wall, data);
	while (rdr.y < (int)data->res.y)
	{
		if (rdr.y < (double)data->res.y / 2 - wall_h(1, rdr, data))
			img_add_pixel(0, data->col_ceil, rdr, data);
		else if (rdr.y < (double)data->res.y / 2 + wall_h(0, rdr, data))
			img_add_pixel(1, get_pixel(rdr, tex, wall, data), rdr, data);
		else
			img_add_pixel(2, data->col_floor, rdr, data);
		rdr.y++;
	}
}

t_wall			check_hit(double fdr[6], t_pos idr[2], t_data *data)
{
	t_wall	res;

	while (1)
	{
		res.side = ((fdr[DISTX] < fdr[DISTY] && fdr[ORIX] != 0)
				|| fdr[ORIY] == 0);
		idr[POS].x += res.side ? idr[STEP].x : 0;
		idr[POS].y += res.side ? 0 : idr[STEP].y;
		if (data->map[idr[POS].x % data->smap.x][idr[POS].y % data->smap.y] ==
				MAPWALL)
		{
			res.dist = fdr[res.side ? DISTX : DISTY];
			res.x = res.dist * fdr[ORIX] + data->x;
			res.y = res.dist * fdr[ORIY] + data->y;
			return (res);
		}
		fdr[DISTX] += res.side ? fdr[DELTAX] : 0;
		fdr[DISTY] += res.side ? 0 : fdr[DELTAY];
	}
}
