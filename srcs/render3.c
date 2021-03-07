/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:22:54 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 11:23:28 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "utils.h"
#include "struct.h"

t_sprite		**retrieve_sprites(t_data *data)
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
