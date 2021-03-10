/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:55:26 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/10 15:56:58 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "utils.h"
#include "struct.h"
#include "mlx.h"

void			mlx_null(t_data *data)
{
	int		i;

	data->ptr = NULL;
	data->win = NULL;
	i = -1;
	while (++i < USHRT_MAX)
		data->kpr[i] = 0;
	i = -1;
	while (++i < NB_TEXTURE)
		img_null(data->tex + i);
	img_null(&data->scn);
	data->wdist = NULL;
}

static void		set_sprites(t_data *data)
{
	t_pos	pos;
	int		i;

	i = 0;
	pos.y = 0;
	data->sprites = maybemalloc(data->nb_sprites * sizeof(t_sprite), data);
	while (pos.y < data->smap.y)
	{
		pos.x = 0;
		while (pos.x < data->smap.x)
		{
			if (data->map[pos.x][pos.y] == MAPSPRITE)
			{
				data->sprites[i].x = (double)pos.x + 0.5;
				data->sprites[i].y = (double)pos.y + 0.5;
				i++;
			}
			pos.x++;
		}
		pos.y++;
	}
}

static void		set_start(t_data *data)
{
	int		x;
	int		y;

	x = -1;
	while (++x < data->smap.x)
	{
		y = -1;
		while (++y < data->smap.y)
		{
			if (data->map[x][y] >= MAPNORTH && data->map[x][y] <= MAPWEST)
			{
				data->x = (double)x + 0.5;
				data->y = (double)y + 0.5;
				data->ox = (data->map[x][y] == MAPEAST)
						- (data->map[x][y] == MAPWEST);
				data->oy = (data->map[x][y] == MAPSOUTH)
						- (data->map[x][y] == MAPNORTH);
				return ;
			}
		}
	}
}

void			new_mlx(char *prog_name, t_data *data)
{
	int		i;
	int		res[2];

	if (!(data->ptr = mlx_init()))
		ft_error(EMLX, data);
	mlx_get_screen_size(data->ptr, &res[0], &res[1]);
	data->res.x = data->res.x > res[0] && !data->save ? res[0] : data->res.x;
	data->res.y = data->res.y > res[1] && !data->save ? res[1] : data->res.y;
	if (!data->save && !(data->win = mlx_new_window(data->ptr, data->res.x,
					data->res.y, prog_name)))
		ft_error(EMLX, data);
	set_start(data);
	set_sprites(data);
	i = -1;
	while (++i < NB_TEXTURE)
		new_tex(i, &(data->tex[i]), data);
	new_img(&data->scn, (int)data->res.x, (int)data->res.y, data);
	data->wdist = maybemalloc(sizeof(double) * data->res.x, data);
}

void			free_mlx(t_data *data)
{
	int		i;

	i = -1;
	while (++i < NB_TEXTURE)
		free_img(data->tex + i, data);
	free_img(&data->scn, data);
	if (data->win)
		mlx_destroy_window(data->ptr, data->win);
	if (data->ptr)
	{
		mlx_destroy_display(data->ptr);
		free(data->ptr);
	}
	if (data->wdist)
		free(data->wdist);
	mlx_null(data);
}
