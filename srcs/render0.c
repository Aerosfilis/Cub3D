/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:08:25 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/06 19:13:51 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "utils.h"
#include "mlx.h"
#include "struct.h"

void		new_screen(t_data *data)
{
	t_mlx	*mlx;

	mlx = &(data->mlx);
	if (!(mlx->scn = mlx_new_image(mlx->ptr, (int)data->res.x,
				(int)data->res.y)))
		ft_error(EMLX, data);
}

void		destroy_screen(t_data *data)
{
	mlx_destroy_image(data->mlx.ptr, data->mlx.scn);
	data->mlx.scn = NULL;
}
