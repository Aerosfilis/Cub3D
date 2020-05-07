/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:18:50 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/07 17:09:43 by cbugnon          ###   ########.fr       */
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

size_t		ft_strlen(const char *str);
int			stoi(const char *str);
ssize_t		str_append(char **s1, const char *s2, ssize_t len, t_data *data);
void		ft_error(int err, t_data *data);

#endif
