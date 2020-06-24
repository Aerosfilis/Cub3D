/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:36:12 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/24 10:48:22 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <sys/types.h>
# include "struct.h"

# define FOV 66.0

typedef struct	s_wall
{
	double		x;
	double		y;
	double		dist;
	int			side;
}				t_wall;

typedef struct	s_vert_render
{
	int			x;
	int			y;
	double		dist;
	double		cos;
	double		sin;
}				t_vert_render;

void			cycle_angle(t_mlx *mlx, t_data *data);
t_wall			next_wall(double ox, double oy, t_mlx *mlx, t_data *data);

#endif
