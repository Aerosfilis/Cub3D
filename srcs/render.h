/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:36:12 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 11:22:00 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <sys/types.h>
# include "struct.h"

# define FOV 66.0
# define CROUCH 0.1

# define POS 0
# define STEP 1

# define DISTX 0
# define DISTY 1
# define DELTAX 2
# define DELTAY 3
# define ORIX 4
# define ORIY 5

# ifndef SHADOW
#  define SHADOW 0
# endif

typedef struct	s_wall
{
	double		x;
	double		y;
	double		dist;
	int			side;
}				t_wall;

typedef struct	s_vrdr
{
	int			x;
	int			y;
	double		dist;
	double		cos;
	double		sin;
}				t_vrdr;

void			cycle_angle(t_data *data);
void			draw_sprites(t_data *data);
void			img_add_pixel(int option, int rgb, t_vrdr rdr, t_data *data);
void			draw_vertical(t_vrdr rdr, t_wall wall, t_data *data);
t_wall			check_hit(double fdr[6], t_pos idr[2], t_data *data);
t_sprite		**retrieve_sprites(t_data *data);

#endif
