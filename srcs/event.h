/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:06:20 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/05 22:44:31 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include <sys/types.h>
# include <limits.h>
# include "struct.h"

int key_press(int key, t_mlx *mlx);
int key_release(int, t_mlx *mlx);
int loop(t_data *data);

#endif
