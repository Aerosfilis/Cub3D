/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:42:11 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/06 17:42:28 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <limits.h>
#include "event.h"
#include "struct.h"

int		key_press(int key, t_mlx *mlx)
{
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->kpr[key] = 1;
	mlx->kpr[KS] += (key == KW && mlx->kpr[KS] == 1);
	mlx->kpr[KW] += (key == KS && mlx->kpr[KW] == 1);
	mlx->kpr[KD] += (key == KA && mlx->kpr[KD] == 1);
	mlx->kpr[KA] += (key == KD && mlx->kpr[KA] == 1);
	return (0);
}

int		key_release(int key, t_mlx *mlx)
{
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->kpr[key] = 0;
	mlx->kpr[KS] -= (key == KW && mlx->kpr[KS] == 2);
	mlx->kpr[KW] -= (key == KS && mlx->kpr[KW] == 2);
	mlx->kpr[KD] -= (key == KA && mlx->kpr[KD] == 2);
	mlx->kpr[KA] -= (key == KD && mlx->kpr[KA] == 2);
	return (0);
}

int		loop(t_data *data)
{
	(void)data;
	return (0);
}
