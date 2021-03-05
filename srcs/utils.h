/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:18:50 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/05 07:51:56 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include <stdlib.h>
# include <errno.h>
# include "struct.h"

# define ESPNULL -1
# define ENULLPTR -2
# define EINVSET -3
# define EINVMAP -4
# define EINVARG -5
# define EMLX -6
# define ETEXTURE -7
# define EBPP -8

# define BUFSIZE 1025

int		ft_strlen(const char *str);
int		stoi(const char *str);
void	*maybemalloc(int size, t_data *data);
int		str_append(char **s1, const char *s2, int len, t_data *data);
void	ft_error(int err, t_data *data);

int		gnl(const int fd, char **line, t_data *data);
int		get_function(const char *l);
int		rgbtoi(int rgb[3]);

#endif
