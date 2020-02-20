/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:24:07 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 17:37:32 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t		ft_strlen(const char *str)
{
	size_t		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

size_t		djb2(const char *str)
{
	size_t		hash;
	size_t		i;

	if (!str)
		return (0);
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
	return (c == ' ' || c == '\n' || c == '\f' || c == '\t' || c == '\r'
			|| c == '\v');
}

ssize_t		hash_lookup(const size_t *hash_tab, const size_t hash)
{
	size_t		i;

	i = 0;
	if (!hash_tab)
		return (-1);
	while (hash_tab[i])
	{
		if (hash_tab[i] == hash)
			return (i);
		i++;
	}
	return (-1);
}

int			stoi(const char *str)
{
	long	res;
	int		i;
	int		neg;

	if (!str)
		return (0);
	neg = (str[0] == '-');
	res = 0;
	i = neg;
	while (str[i])
	{
		res = res * 10 + str[i] + 48;
		i++;
	}
	if (neg)
		res = -res;
	return (res);
}
