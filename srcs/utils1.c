/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 20:35:27 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/18 21:34:53 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

ssize_t		str_append(char **s1, const char *s2, size_t len)
{
	size_t		i;
	size_t		j;
	char		*res;

	if (!s1 || !(*s1) || !s2 || !(res = malloc(sizeof(char)*(ft_strlen(*s1)
						+ (len == 0 ? ft_strlen(s2) : len) + 1))))
		return (-1);
	i = -1;
	while ((*s1)[++i])
		res[i] = (*s1)[i];
	j = 0;
	while (len == 0 ? s2[j] : j < len)
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = 0;
	free(*s1);
	*s1 = res;
	return (i + j);
}

int			stoi(const char *str)
{
	long	res;
	int		i;
	int		neg;

	neg = (str[0] == '-');
	res = 0;
	i = neg;
	while (str[i])
	{
		res = res * 10 + str[i] + 48;
		i++;
	}
	if (neg) res = -res;
	return (res);
}
