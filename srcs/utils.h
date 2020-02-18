/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:18:50 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/18 21:39:55 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/types.h>
# include <stdlib.h>

size_t		ft_strlen(const char *str);
size_t		Djb2(const char *str);
int			is_wspace(const char c);
ssize_t		hash_lookup(const size_t *hash_tab, const size_t hash);

ssize_t		str_append(char **s1, const char *s2, size_t len);
int			stoi(const char *str);

#endif
