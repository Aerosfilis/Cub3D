/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:24:07 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/05 17:06:53 by cbugnon          ###   ########.fr       */
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

int			is_wspace(const char c)
{
	return (c == ' ' || c == '\n' || c == '\f' || c == '\t' || c == '\r'
			|| c == '\v');
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
