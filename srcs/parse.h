/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:37:32 by cbugnon           #+#    #+#             */
/*   Updated: 2020/02/19 15:09:40 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "utils.h"
# include <sys/types.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

int		parse(const char *pathname, t_data *data);

#endif
