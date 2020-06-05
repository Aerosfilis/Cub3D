/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:18:50 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/05 22:10:28 by cbugnon          ###   ########.fr       */
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

# define BUFSIZE 1024

size_t		ft_strlen(const char *str);
int			stoi(const char *str);
void		*maybemalloc(size_t size, t_data *data);
ssize_t		str_append(char **s1, const char *s2, ssize_t len, t_data *data);
void		ft_error(int err, t_data *data);

ssize_t		gnl(const int fd, char **line, t_data *data);
int			get_function(const char *l);
int			rgbtoi(int rgb[3]);

#endif
