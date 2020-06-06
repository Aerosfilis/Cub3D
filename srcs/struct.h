/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:31:19 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/06 19:02:18 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>
# include <stdlib.h>
# include <errno.h>
# include <limits.h>

# define TEX_SPRITE 0
# define TEX_NO 1
# define TEX_SO 2
# define TEX_WE 3
# define TEX_EA 4
# define NB_TEXTURE 5

# define MAPEMPTY 0
# define MAPWALL 1
# define MAPSPRITE 10
# define MAPNORTH 50
# define MAPSOUTH 51
# define MAPEAST 52
# define MAPWEST 53

# define UNIT 100
# define RADDIV 200

# ifdef __linux__
#  define KW 119
#  define KA 97
#  define KS 115
#  define KD 100
#  define SH 65505
#  define ES 65307
# else
#  define KW 13
#  define KA 0
#  define KS 1
#  define KD 2
#  define SH 257
#  define ES
# endif

typedef struct		s_pos
{
	size_t			x;
	size_t			y;
}					t_pos;

typedef struct		s_wall
{
	t_pos			pos;
	void			*tex;
}					t_wall;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
	unsigned char	kpr[USHRT_MAX];
	t_pos			chr;
	int				ori;
	int				height;
	void			*tex[NB_TEXTURE];
	t_pos			tres[NB_TEXTURE];
	void			*scn;
}					t_mlx;

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

void				mlx_null(t_mlx *mlx);
void				new_mlx(t_mlx *mlx, char *prog_name, t_data *data);
void				free_mlx(t_mlx *mlx);
void				new_pos(t_pos *pos, size_t x, size_t y);

#endif
