/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:37:32 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/20 14:38:03 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "utils.h"
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

void		parse(const char *pathname, t_data *data);
ssize_t		get_next_line(const int fd, char **line);
int			proc_line(char *line, t_data *data);
void		set_data_texture(const *line, const size_t hash, t_data *data);
void		set_data_color(const *line, const size_t hash, t_data *data);
void		set_data_res(const *line, const size_t hash, t_data *data);
void		set_data_map(const *line, const size_t hash, t_data *data);

#endif
