/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:30:05 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 13:58:33 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"
#include "render_bonus.h"
#include "utils.h"

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
	pixel = (int)(tex->x * tex_x) * tex->bpp / 8 + (int)(tex->y * tex_y)
		* tex->sl;
	rgb[0] = (unsigned char)tex->addr[tex->endian ?
		3 * tex->bpp / 32 : pixel + tex->bpp / 16];
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
		1)) * (double)data->res.x / sprite->adj_x / tan(FOV / 360 * M_PI);
	end = ((double)data->res.y - 1) / 2 + (0.25 - CROUCH * (data->kpr[CT] ==
		1)) * (double)data->res.x / sprite->adj_x / tan(FOV / 360 * M_PI);
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
	t_vrdr			rdr;
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
