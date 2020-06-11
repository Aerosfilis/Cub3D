/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 19:28:05 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/11 01:43:45 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"

double	dist_pts(t_pos a, t_pos b)
{
	double	dx;
	double	dy;

	dx = (long double)(sprite.x - origin.x) / UNIT;
	dy = (long double)(sprite.y - origin.y) / UNIT;
	return (sqrt(dx * dx + dy * dy));
}

double	dist_sprite(t_pos origin, t_pos sprite, int ang)
{
	return (dist_pts(origin, sprite) * cos((double)ang / 2 * M_PI / RADDIV));
}

double	land_sprite(t_pos origin, t_pos sprite, int ang)
{
	return (dist_pts(origin, sprite) * sin((double)ang / 2 * M_PI / RADDIV));
}
