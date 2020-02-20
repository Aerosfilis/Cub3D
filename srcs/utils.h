/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:18:50 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 13:45:47 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include <stdlib.h>
# include "struct.h"

# define ESPNULL -1
# define ENULLPTR -2

size_t		ft_strlen(const char *str);
size_t		djb2(const char *str);
int			is_wspace(const char c);
ssize_t		hash_lookup(const size_t *hash_tab, const size_t hash);
int			stoi(const char *str);

ssize_t		str_append(char **s1, const char *s2, size_t len, t_data *data);
void		ft_error(int err, t_data *data);

#endif
