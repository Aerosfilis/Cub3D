/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:24:07 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/18 20:33:57 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t		ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t		Djb2(const char *str)
{
	size_t		hash;
	size_t		i;

	hash = 5381;
	i = 0;
	while (str[i])
	{
		hash = (hash << 5) + hash + str[i];
		i++;
	}
	return (hash);
}

int			is_wspace(const char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c =='\t' || c == '\r'
			|| c == '\v');
}

ssize_t		hash_lookup(const size_t *hash_tab, const size_t hash)
{
	size_t		i;

	i = 0;
	while (hash_tab[i])
	{
		if (hash_tab[i] == hash)
			return (i);
		i++;
	}
	return (-1);
}
