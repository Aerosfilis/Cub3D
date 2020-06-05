/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:06:20 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/05 18:28:53 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include <sys/types.h>
#include <limits.h>

int key_press_event(int key, t_mlx *mlx)
{
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->k_press[key] = 1;
	mlx->k_press[KS] += (key == KW && mlx->k_press[KS] == 1);
	mlx->k_press[KW] += (key == KS && mlx->k_press[KW] == 1);
	mlx->k_press[KD] += (key == KA && mlx->k_press[KD] == 1);
	mlx->k_press[KA] += (key == KD && mlx->k_press[KA] == 1);
 	return (0);
}

int key_release_event(int key, t_mlx *mlx)
{
	if (key >= USHRT_MAX || key < 0)
		return (0);
	mlx->k_press[key] = 0;
	mlx->k_press[KS] -= (key == KW && mlx->k_press[KS] == 2);
	mlx->k_press[KW] -= (key == KS && mlx->k_press[KW] == 2);
	mlx->k_press[KD] -= (key == KA && mlx->k_press[KD] == 2);
	mlx->k_press[KA] -= (key == KD && mlx->k_press[KA] == 2);
	return (0);
}

int loop_event(t_data *data)
{
	(void)data;
	return (0); 
}
