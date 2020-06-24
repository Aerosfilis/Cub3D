/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:06:20 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/24 10:24:26 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include <sys/types.h>
# include <limits.h>
# include "struct.h"

# define MOVSPD 0.05
# define SPRINT 2
# define ROTSPD 0.05

int key_press(int key, t_mlx *mlx);
int key_release(int key, t_mlx *mlx);
int loop(t_data *data);

#endif
