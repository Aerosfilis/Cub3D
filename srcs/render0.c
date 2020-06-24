/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:08:25 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/24 10:42:11 by cbugnon          ###   ########.fr       */
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

t_img			*get_texture(t_wall wall, t_data *data)
{
	long	res = wall.side + 2 *(wall.side ? (data->mlx.x > wall.x)
			: (data->mlx.y < wall.y));
	(void)data;
	return (void*)res;
}

void			draw_vertical(t_vert_render rdr, t_img *tex, t_mlx *mlx,
								t_data *data)
{
	while (rdr.y < (int)data->res.y)
	{
		if ((double)rdr.y < (double)data->res.y / 2 - 0.25 * (double)data->res.x
				/ rdr.dist / tan(FOV / 360 * M_PI))
			mlx_pixel_put(mlx->ptr, mlx->win, rdr.x, rdr.y, data->col_ceil);
		else if (rdr.y < ((double)data->res.y / 2 + 0.25 *
				(double)data->res.x / rdr.dist / tan(FOV / 360 * M_PI)))
			mlx_pixel_put(mlx->ptr, mlx->win, rdr.x, rdr.y,
					(int)(long)tex * 85);
		else
			mlx_pixel_put(mlx->ptr, mlx->win, rdr.x, rdr.y, data->col_floor);
		rdr.y++;
	}
}

void			cycle_angle(t_mlx *mlx, t_data *data)
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
		wall = next_wall(mlx->ox * rdr.cos - mlx->oy * rdr.sin,
			mlx->ox * rdr.sin + mlx->oy * rdr.cos, mlx, data);
		rdr.dist = wall.dist * rdr.cos;
		mlx->wdist[rdr.x] = rdr.dist;
		rdr.y = 0;
		draw_vertical(rdr, get_texture(wall, data), mlx, data);
		rdr.x++;
	}
}

static t_wall	check_hit(double fdr[6], t_pos idr[2], t_mlx *mlx, t_data *data)
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
			res.x = res.dist * fdr[ORIX] + mlx->x;
			res.y = res.dist * fdr[ORIY] + mlx->y;
			return (res);
		}
		fdr[DISTX] += res.side ? fdr[DELTAX] : 0;
		fdr[DISTY] += res.side ? 0 : fdr[DELTAY];
	}
}

t_wall	next_wall(double ox, double oy, t_mlx *mlx, t_data *data)
{
	double	fdr[6];
	t_pos	idr[2];

	fdr[ORIX] = ox;
	fdr[ORIY] = oy;
	fdr[DELTAX] = (ox == 0 ? 1 : fabs(1 / ox));
	fdr[DELTAY] = (oy == 0 ? 1 : fabs(1 / oy));
	idr[STEP].x = (ox < 0.0 ? -1 : 1);
	idr[STEP].y = (oy < 0.0 ? -1 : 1);
	idr[POS].x = (size_t)mlx->x;
	idr[POS].y = (size_t)mlx->y;
	fdr[DISTX] = (ox < 0 ? mlx->x - idr[POS].x : 1 - mlx->x + idr[POS].x) *
		fdr[DELTAX];
	fdr[DISTY] = (oy < 0 ? mlx->y - idr[POS].y : 1 - mlx->y + idr[POS].y) *
		fdr[DELTAY];
	return (check_hit(fdr, idr, mlx, data));
}
