/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:08:25 by cbugnon           #+#    #+#             */
/*   Updated: 2020/08/15 20:25:17 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <math.h>
#include "render.h"
#include "utils.h"
#include "mlx.h"
#include "struct.h"

#define POS 0
#define STEP 1

#define DISTX 0
#define DISTY 1
#define DELTAX 2
#define DELTAY 3
#define ORIX 4
#define ORIY 5

#define CROUCH 0.1

#include <stdio.h>
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

double			wall_h(int option, t_vert_render rdr, t_data *data)
{
	return ((0.25 + CROUCH * (option && data->kpr[CT] == 1)
			- 0.1 * (!option && data->kpr[CT] == 1))
			* (double)data->res.x / rdr.dist / tan(FOV / 360 * M_PI));
}

unsigned int	get_pixel(t_vert_render rdr, t_img *restrict tex, t_wall wall,
							t_data *restrict data)
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
		pixel + 3 * tex->bpp / 32 : pixel] * tex->bpp / 32;
	return (rgbtoi(rgb));
}

void			img_add_pixel(int option, int rgb, t_vert_render rdr,
								t_data *data)
{
	int				i;
	unsigned int	col;
	double			tmp;

	i = 0;
	col = mlx_get_color_value(data->ptr, rgb);
	tmp = ((double)data->scn.x / 2 / ((option == 0) * ((double)data->scn.y / 2 -
		(double)rdr.y) + (option == 2) * ((double)rdr.y - (double)data->scn.y /
		2) + (option == 1)) / tan(FOV * M_PI / 360) / rdr.cos * (option != 1) +
		(rdr.dist > 2 ? rdr.dist - 1 : 1) * (option == 1)) * (SHADOW == 1)
		+ (SHADOW == 0);
	while (i * 8 < data->scn.bpp)
	{
		if (rdr.x < data->scn.x && rdr.y < data->scn.y)
		{
			data->scn.addr[(data->scn.endian ?
					(rdr.x + 1) * data->scn.bpp / 8 - i - 1 :
					rdr.x * data->scn.bpp / 8 + i)
				+ rdr.y * data->scn.sl] = ((col >> (i * 8)) & 255) / tmp;
		}
		i++;
	}
}

void			draw_vertical(t_vert_render rdr, t_wall wall, t_data *data)
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

void			cycle_angle(t_data *data)
{
	t_vert_render	rdr;
	t_wall			wall;
	double			sn;
	static double	cs = 0;

	rdr.x = 0;
	if (cs == 0)
		cs = ((double)data->res.x + 1) / 2 / tan(FOV * M_PI / 360);
	while (rdr.x < (int)data->res.x)
	{
		sn = (double)rdr.x - ((double)data->res.x - 1) / 2;
		rdr.sin = sqrt(cs * cs + sn * sn);
		rdr.cos = cs / rdr.sin;
		rdr.sin = sn / rdr.sin;
		wall = next_wall(data->ox * rdr.cos - data->oy * rdr.sin,
			data->ox * rdr.sin + data->oy * rdr.cos, data);
		rdr.dist = wall.dist * rdr.cos;
		data->wdist[rdr.x] = rdr.dist;
		rdr.y = 0;
		draw_vertical(rdr, wall, data);
		rdr.x++;
	}
}

static t_wall	check_hit(double fdr[6], t_pos idr[2], t_data *data)
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

t_wall			next_wall(double ox, double oy, t_data *data)
{
	double	fdr[6];
	t_pos	idr[2];

	fdr[ORIX] = ox;
	fdr[ORIY] = oy;
	fdr[DELTAX] = (ox == 0 ? 1 : fabs(1 / ox));
	fdr[DELTAY] = (oy == 0 ? 1 : fabs(1 / oy));
	idr[STEP].x = (ox < 0.0 ? -1 : 1);
	idr[STEP].y = (oy < 0.0 ? -1 : 1);
	idr[POS].x = (size_t)data->x;
	idr[POS].y = (size_t)data->y;
	fdr[DISTX] = (ox < 0 ? data->x - idr[POS].x : 1 - data->x + idr[POS].x) *
		fdr[DELTAX];
	fdr[DISTY] = (oy < 0 ? data->y - idr[POS].y : 1 - data->y + idr[POS].y) *
		fdr[DELTAY];
	return (check_hit(fdr, idr, data));
}
