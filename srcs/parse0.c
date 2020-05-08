/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:44:44 by cbugnon           #+#    #+#             */
/*   Updated: 2020/05/08 14:19:05 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

const void		(*g_set_data[8])(const char *, t_data *) =
{
	set_data_res,
	set_data_tex,
	set_data_col,
	set_data_map
};

void			parse(const char *pathname, t_data *data)
{
	char	*line;

	if ((data->mapfd = open(pathname, O_RDONLY)) < 0)
		ft_error(errno, data);
	if (data->map)
		free_datamap(data);
	init_map(data, data->mapfd);
	close(data->mapfd);
	data->mapfd = 0;
	if ((data->mapfd = open(pathname, O_RDONLY)) < 0)
	   ft_error(errno, data);	
	while (gnl(data->mapfd, &line, data) >= 0)
	{
		if (get_function(line) >= 0)
			(g_set_data[get_function(line)])(line, data);
		free(line);
	}
	free(line);
	close(data->mapfd);
}

#include <stdio.h>
void			set_data_res(const char *line, t_data *data)
{
	printf("set data res\n");
}
void			set_data_tex(const char *line, t_data *data)
{
	printf("set data tex\n");
}
void			set_data_col(const char *line, t_data *data)
{
	printf("set data col\n");
}
void			set_data_map(const char *line, t_data *data)
{
	printf("set data map\n");
}
