/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:08:25 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/11 04:56:29 by cbugnon          ###   ########.fr       */
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

static t_wall	check_hit(double fdr[6], t_pos idr[2], t_mlx *mlx, t_data *data)
{
	t_wall	res;

	while (1)
	{
		res.side = ((fdr[DISTX] < fdr[DISTY] && fdr[ORIX] != 0)
				|| fdr[ORIY] == 0);
		idr[POS].x += res.side ? idr[STEP].x : 0;
		idr[POS].y += res.side ? 0 : idr[STEP].y;
		if (data->map[idr[POS].x][idr[POS].y] == MAPWALL)
		{
			res.dist = fdr[res.side ? DISTX : DISTY];
			res.x = res.dist * fdr[ORIX] * (fdr[ORIX] != 0) + mlx->x;
			res.y = res.dist * fdr[ORIY] * (fdr[ORIY] != 0) + mlx->y;
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
	idr[STEP].x = (ox < 0 ? -1 : 1);
	idr[STEP].y = (oy < 0 ? -1 : 1);
	idr[POS].x = (size_t)mlx->x;
	idr[POS].y = (size_t)mlx->y;
	fdr[DISTX] = (ox < 0 ? mlx->x - idr[POS].x : 1 - mlx->x + idr[POS].x) *
		fdr[DELTAX];
	fdr[DISTY] = (oy < 0 ? mlx->y - idr[POS].y : 1 - mlx->y + idr[POS].y) *
		fdr[DELTAY];
	return (check_hit(fdr, idr, mlx, data));
}
