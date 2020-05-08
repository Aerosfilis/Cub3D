/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:31:19 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 16:10:29 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <stdlib.h>
# include <errno.h>

# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define TEX_SPRITE 4
# define NB_TEXTURE 5

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
	t_pos			smap;
	char			**map;
	char			*path_tex[NB_TEXTURE];
	int				col_ceil;
	int				col_floor;
	char			*err_msg;
	t_mlx			mlx;
	int				mapfd;
}					t_data;

void				new_data(t_data *data, char *prog_name);
void				free_datamap(t_data *data);
void				free_data(t_data *data);
void				set_map(t_data *data);

void				new_mlx(t_mlx *mlx);
void				free_mlx(t_mlx *mlx);
void				new_pos(t_pos *pos, ssize_t x, ssize_t y);

#endif
