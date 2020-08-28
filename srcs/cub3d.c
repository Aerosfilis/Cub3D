/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:34:31 by cbugnon           #+#    #+#             */
/*   Updated: 2020/08/25 20:06:50 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "parse.h"
#include "render.h"
#include "event.h"
#include "struct.h"
#include "utils.h"
#include "mlx.h"

#ifndef SHADOW
# define SHADOW 0
#endif

static int	check_arg(int ac, char **av, t_data *data)
{
	size_t	i;

	if (ac < 2 || ac > 3 || (ac == 3 && (av[2][0] != '-' || av[2][1] != '-'
			|| av[2][2] != 's' || av[2][3] != 'a' || av[2][4] != 'v'
			|| av[2][5] != 'e' || av[2][6] != 0)))
		ft_error(EINVARG, data);
	i = ft_strlen(av[1]) - 1;
	if (av[1][i] != 'b' || av[1][i - 1] != 'u' || av[1][i - 2] != 'c'
			|| av[1][i - 3] != '.')
		ft_error(EINVARG, data);
	return (ac == 3);
}

#include <stdio.h>
int			main(int ac, char **av)
{
	t_data	data;

	new_data(&data, av[0]);
	check_arg(ac, av, &data);
	parse(av[1], &data);
	new_mlx(av[0], &data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 1L << 17, quit_cubed, &data);
	mlx_loop_hook(data.ptr, loop, &data);
	mlx_loop(data.ptr);
	ft_error(EMLX, &data);
}
