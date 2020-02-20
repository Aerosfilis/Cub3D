/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:31:19 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 13:55:02 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <stdlib.h>

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct		s_pos
{
	ssize_t			x;
	ssize_t			y;
}					t_pos;

typedef struct		s_data
{
	t_pos			res;
	t_pos			map_size;
	unsigned char	**map;
	char			*path_NO;
	char			*path_SO;
	char			*path_WE;
	char			*path_EA;
	int				color_ceil;
	int				color_floor;
	char			*err_msg;
	t_mlx			mlx;
}					t_data;

void		new_data(t_data *data, char *prog_name);
void		free_data(t_data *data);
void		new_pos(t_pos *pos, ssize_t x, ssize_t y);

void		new_mlx(t_mlx *mlx);
void		free_mlx(t_mlx *mlx);

#endif
