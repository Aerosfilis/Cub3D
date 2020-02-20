/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:18:50 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 11:49:24 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include <stdlib.h>

# define ESPNULL -1
# define ENULLPTR -2

char		*g_errlst[]=
{
	"\n",
	": String pointer null\n",
	": Null pointer passed\n"
};

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct		s_data
{
	size_t			res_x;
	size_t			res_y;
	size_t			map_x;
	size_t			map_y;
	unsigned char	**map;
	char			*path_NO;
	char			*path_SO;
	char			*path_WE;
	char			*path_EA;
	int				color_ceil;
	int				color_floor;
	char			*err_msg;
	t_mlx			*mlx;
}					t_data;

size_t		ft_strlen(const char *str);
size_t		djb2(const char *str);
int			is_wspace(const char c);
ssize_t		hash_lookup(const size_t *hash_tab, const size_t hash);
int			stoi(const char *str);

ssize_t		str_append(char **s1, const char *s2, size_t len, t_data *data);
void		ft_error(int err, t_data *data);
t_data		*new_data(char *prog_name);
void		free_data(t_data **data);

void		free_mlx(t_mlx *mlx);

#endif
