/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:06:20 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/27 13:51:16 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include <sys/types.h>
# include <limits.h>
# include "struct.h"

# define MOVSPD 0.15
# define SPRINT 2
# define ROTSPD 0.1
# define COLISIZE 0.1

int key_press(int key, t_mlx *mlx);
int key_release(int key, t_mlx *mlx);
int loop(t_data *data);

#endif
