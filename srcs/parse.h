/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:37:32 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 13:48:59 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <sys/types.h>
# include "struct.h"

void		parse(const char *pathname, t_data *data);
void		set_data_res(const char *line, t_data *data);
void		set_data_tex(const char *line, t_data *data);
void		set_data_col(const char *line, t_data *data);
void		set_data_map(const char *line, t_data *data);

#endif
