/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:37:32 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/18 22:15:49 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "utils.h"
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

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
}					t_data

int		parse(const char *pathname, t_data *data);

#endif
