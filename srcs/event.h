/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:06:20 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/07 14:26:49 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include <sys/types.h>
# include <limits.h>
# include "struct.h"

# define MOVSPD 0.05
# define SPRINT 1.5
# define ROTSPD 0.035

# define WRAP 0.9

int key_press(int key, t_data *data);
int key_release(int key, t_data *data);
int	quit_cubed(t_data *data);
int loop(t_data *data);

#endif
