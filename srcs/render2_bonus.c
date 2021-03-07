/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:07:59 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 15:11:48 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"
#include "render_bonus.h"
#include "utils.h"
#include "mlx.h"

void			depth_32(double sha, unsigned int col, t_vrdr rdr, t_data *data)
{
	static int	endian = -1;
	int			i;

	if (endian < 0)
		endian = data->scn.endian;
	if (endian)
	{
		i = (rdr.x + 1) * 4 - 2 + rdr.y * data->scn.sl;
		data->scn.addr[i] = ((col >> 8) & 255) / sha;
		data->scn.addr[i - 1] = ((col >> 16) & 255) / sha;
		data->scn.addr[i - 2] = ((col >> 24) & 255) / sha;
	}
	else
	{
		i = rdr.x * 4 + rdr.y * data->scn.sl;
		data->scn.addr[i] = (col & 255) / sha;
		data->scn.addr[i + 1] = ((col >> 8) & 255) / sha;
		data->scn.addr[i + 2] = ((col >> 16) & 255) / sha;
	}
}

void			depth_24(double sha, unsigned int col, t_vrdr rdr, t_data *data)
{
	static int	endian = -1;
	int			i;

	if (endian < 0)
		endian = data->scn.endian;
	if (data->scn.endian)
	{
		i = (rdr.x + 1) * 3 - 1 + rdr.y * data->scn.sl;
		data->scn.addr[i] = (col & 255) / sha;
		data->scn.addr[i - 1] = ((col >> 8) & 255) / sha;
		data->scn.addr[i - 2] = ((col >> 16) & 255) / sha;
	}
	else
	{
		i = rdr.x * 3 + rdr.y * data->scn.sl;
		data->scn.addr[i] = (col & 255) / sha;
		data->scn.addr[i + 1] = ((col >> 8) & 255) / sha;
		data->scn.addr[i + 2] = ((col >> 16) & 255) / sha;
	}
}

void			img_add_pixel(int option, int rgb, t_vrdr rdr, t_data *data)
{
	unsigned int	col;
	double			sha;

	if (rdr.x >= data->scn.x || rdr.y >= data->scn.y)
		return ;
	col = mlx_get_color_value(data->ptr, rgb);
	sha = 1;
	if (option != 1)
	{
		sha = (double)data->scn.x / 2 / tan(FOV * M_PI / 360) / rdr.cos;
		if (option == 0)
			sha /= ((double)data->scn.y / 2 - (double)rdr.y);
		else if (option == 2)
			sha /= ((double)rdr.y - (double)data->scn.y / 2);
	}
	else
		sha = rdr.dist > 2 ? rdr.dist - 1 : 1;
	if (data->scn.bpp == 32)
		depth_32(sha, col, rdr, data);
	else if (data->scn.bpp == 24)
		depth_24(sha, col, rdr, data);
	else
		ft_error(EBPP, data);
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

void			cycle_angle(t_data *data)
{
	t_vrdr			rdr;
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
