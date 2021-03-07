/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 12:07:43 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 14:27:55 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "struct.h"
#include "event_bonus.h"
#include "render_bonus.h"

int				key_press(int key, t_data *data)
{
	if (key == ES)
		quit_cubed(data);
	if (key >= USHRT_MAX || key < 0)
		return (0);
	data->kpr[key] = 1;
	data->kpr[KS] += (key == KW && data->kpr[KS] == 1);
	data->kpr[KW] += (key == KS && data->kpr[KW] == 1);
	data->kpr[KD] += (key == KA && data->kpr[KD] == 1);
	data->kpr[KA] += (key == KD && data->kpr[KA] == 1);
	data->kpr[AL] += (key == AR && data->kpr[AL] == 1);
	data->kpr[AR] += (key == AL && data->kpr[AR] == 1);
	return (0);
}

int				key_release(int key, t_data *data)
{
	if (key >= USHRT_MAX || key < 0)
		return (0);
	data->kpr[key] = 0;
	data->kpr[KS] -= (key == KW && data->kpr[KS] == 2);
	data->kpr[KW] -= (key == KS && data->kpr[KW] == 2);
	data->kpr[KD] -= (key == KA && data->kpr[KD] == 2);
	data->kpr[KA] -= (key == KD && data->kpr[KA] == 2);
	data->kpr[AL] -= (key == AR && data->kpr[AL] == 2);
	data->kpr[AR] -= (key == AL && data->kpr[AR] == 2);
	return (0);
}

int				quit_cubed(t_data *data)
{
	if (data)
		free_data(data);
	exit(EXIT_SUCCESS);
}
