/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:08:25 by cbugnon           #+#    #+#             */
/*   Updated: 2021/02/15 18:42:34 by cbugnon          ###   ########.fr       */
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
t_img	*get_texture(t_wall wall, t_data *data)
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

double	wall_h(int option, t_vrdr rdr, t_data *data)
{
	return ((0.25 + CROUCH * (option && data->kpr[CT] == 1)
		- CROUCH * (!option && data->kpr[CT] == 1))
		*(double)data->res.x / rdr.dist / tan(FOV / 360 * M_PI));
}

unsigned int	get_pixel(t_vrdr rdr, t_img *restrict tex, t_wall wall, t_data *restrict data)
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

void	depth_32(double sha, unsigned int col, t_vrdr rdr, t_data *data)
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

void			depth_24(double sha, unsigned int col, t_vrdr rdr,
							t_data *data)
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

void			img_add_pixel(int option, int rgb, t_vrdr rdr,
								t_data *data)
{
	unsigned int	col;
	double			sha;

	if (rdr.x >= data->scn.x || rdr.y >= data->scn.y)
		return ;
	col = mlx_get_color_value(data->ptr, rgb);
	sha = 1;
	if (SHADOW && option != 1)
	{
		sha = (double)data->scn.x / 2 / tan(FOV * M_PI / 360) / rdr.cos;
		if (option == 0)
			sha /= ((double)data->scn.y / 2 - (double)rdr.y);
		else if (option == 2)
			sha /= ((double)rdr.y - (double)data->scn.y / 2);
	}
	else if (SHADOW)
		sha = rdr.dist > 2 ? rdr.dist - 1 : 1;
	if (data->scn.bpp == 32)
		depth_32(sha, col, rdr, data);
	else if (data->scn.bpp == 24)
		depth_24(sha, col, rdr, data);
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

static t_sprite	**retrieve_sprites(t_data *data)
{
	int				i;
	int				j;
	static t_sprite	**sprites;

	i = 0;
	j = 0;
	sprites = maybemalloc((data->nb_sprites + 1) * sizeof(t_sprite *), data);
	while (i < data->nb_sprites)
	{
		data->sprites[i].adj_x = (data->sprites[i].x - data->x) * data->ox
			- (data->sprites[i].y - data->y) * -data->oy;
		data->sprites[i].adj_y = (data->sprites[i].x - data->x) * -data->oy
			+ (data->sprites[i].y - data->y) * data->ox;
		if (data->sprites[i].adj_x > -1
				&& data->sprites[i].adj_y > -data->sprites[i].adj_x - 1
				&& data->sprites[i].adj_y < data->sprites[i].adj_x + 1)
		{
			sprites[j] = data->sprites + i;
			j++;
		}
		i++;
	}
	sprites[j] = NULL;
	return (sprites);
}

static void		sort_sprites(t_sprite **sprites)
{
	int			idx[3];
	t_sprite	*tmp;

	idx[0] = 0;
	while (sprites[idx[0]])
	{
		idx[1] = 0;
		idx[2] = 0;
		while (sprites[idx[1]])
		{
			if (sprites[idx[2]]->adj_x < sprites[idx[1]]->adj_x)
			{
				tmp = sprites[idx[1]];
				sprites[idx[1]] = sprites[idx[2]];
				sprites[idx[2]] = tmp;
				idx[2] = idx[1];
			}
			else
				idx[2] = idx[1];
			idx[1]++;
		}
		idx[0]++;
	}
}

int				get_sprite_pixel(double tex_x, double tex_y,
							t_data *data)
{
	t_img	*tex;
	int		rgb[3];
	int		pixel;

	tex = data->tex + TEX_SPRITE;
	pixel = (int)(tex->x * tex_x) * tex->bpp / 8 + (int)(tex->y * tex_y) * tex->sl;
	rgb[0] = (unsigned char)tex->addr[tex->endian ?
		 + 3 * tex->bpp / 32 : pixel + tex->bpp / 16];
	rgb[1] = (unsigned char)tex->addr[tex->endian ?
		pixel + tex->bpp / 16 : pixel + tex->bpp / 32];
	rgb[2] = (unsigned char)tex->addr[tex->endian ?
		pixel + tex->bpp / 32 : pixel];
	return (rgbtoi(rgb));
}

void			draw_sprite_col(t_sprite *sprite, t_vrdr rdr,
							double tex_x, t_data *data)
{
	int		start;
	int		end;
	int		col;

	start = ((double)data->res.y - 1) / 2 - (0.25 + CROUCH * (data->kpr[CT] ==
		1)) * (double)data->res.x / sprite->adj_x /tan(FOV / 360 * M_PI);
	end = ((double)data->res.y - 1) / 2 + (0.25 - CROUCH * (data->kpr[CT] ==
		1)) * (double)data->res.x / sprite->adj_x /tan(FOV / 360 * M_PI);
	rdr.y = start >= 0 ? start : 0;
	while (rdr.y < end)
	{
		col = get_sprite_pixel(tex_x, (double)(rdr.y - start) / (end - start),
				data);
		if (col > 0)
			img_add_pixel(1, col, rdr, data);
		rdr.y++;
	}
	(void)tex_x;
}

void			draw_single_sprite(t_sprite *sprite, t_data *data)
{
	t_vrdr	rdr;
	int				start;
	int				end;

	rdr.dist = sprite->adj_x;
	start = ((double)data->res.x - 1) / 2 - (-sprite->adj_y + 0.5) *
		((double)data->res.x - 1) / 2 / sprite->adj_x / tan(FOV * M_PI / 360);
	end = ((double)data->res.x - 1) / 2 - (-sprite->adj_y - 0.5) *
		((double)data->res.x - 1) / 2 / sprite->adj_x / tan(FOV * M_PI / 360);
	rdr.x = start >= 0 ? start : 0;
	while (rdr.x < end && rdr.x < data->res.x)
	{
		if (rdr.x >= 0 && rdr.x < data->res.x && sprite->adj_x <
			data->wdist[rdr.x])
			draw_sprite_col(sprite, rdr, (double)(rdr.x - start) /
					(end - start), data);
		rdr.x++;
	}
}

void			draw_sprites(t_data *data)
{
	int			i;
	t_sprite	**sprites;
	
	sprites = retrieve_sprites(data);
	sort_sprites(sprites);
	i = 0;
	while (sprites[i])
	{
		draw_single_sprite(sprites[i], data);
		i++;
	}
	if (sprites)
		free(sprites);
}
