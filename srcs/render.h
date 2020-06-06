/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:36:12 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/06 18:50:20 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <sys/types.h>
# include "struct.h"

void	new_screen(t_data *data);
void	destroy_screen(t_data *data);
void	draw_sprite(t_pos pos, t_data *data);
void	draw_scene(t_pos pos, t_pos wall, t_data *data);

t_wall	find_wall(int ori, t_data *data);

#endif
