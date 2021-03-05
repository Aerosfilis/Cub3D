/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:31:19 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/05 07:23:21 by cbugnon          ###   ########.fr       */
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

# ifdef __linux__
#  define KW 119
#  define KA 97
#  define KS 115
#  define KD 100
#  define SH 65505
#  define ES 65307
#  define AL 65361
#  define AR 65363
#  define CT 65507
# else
#  define KW 13
#  define KA 0
#  define KS 1
#  define KD 2
#  define SH 257
#  define ES
#  define AL
#  define AR
#  define CT
# endif

typedef struct		s_pos
{
	int				x;
	int				y;
}					t_pos;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			adj_x;
	double			adj_y;
}					t_sprite;

typedef struct		s_img
{
	void *restrict	ptr;
	int				x;
	int				y;
	int				bpp;
	int				sl;
	int				endian;
	char *restrict	addr;
}					t_img;

typedef struct		s_data
{
	t_img				tex[NB_TEXTURE];
	t_img				scn;
	t_sprite			*sprites;
	t_pos				res;
	t_pos				smap;
	double *restrict	wdist;
	double				x;
	double				y;
	double				ox;
	double				oy;
	unsigned char		kpr[USHRT_MAX];
	char *restrict		path_tex[NB_TEXTURE];
	char				*err_msg;
	char **restrict		map;
	void *restrict		ptr;
	void *restrict		win;
	int					col_ceil;
	int					col_floor;
	int					mapfd;
	int					nb_sprites;
}					t_data;

void				new_data(t_data *data, char *prog_name);
void				free_datamap(t_data *data);
void				free_data(t_data *data);
void				set_map(t_data *data);

void				mlx_null(t_data *data);
void				new_mlx(char *prog_name, t_data *data);
void				free_mlx(t_data *data);

void				img_null(t_img *tex);
void				free_img(t_img *tex, t_data *data);
void				new_tex(int i, t_img *tex, t_data *data);
void				new_img(t_img *scn, int x, int y, t_data *data);
void				new_pos(t_pos *pos, size_t x, size_t y);

#endif
