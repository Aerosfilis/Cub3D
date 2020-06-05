/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:34:31 by cbugnon           #+#    #+#             */
/*   Updated: 2020/06/05 22:46:11 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "struct.h"
#include "utils.h"
#include "parse.h"
#include "event.h"
#include "mlx.h"

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

int			main(int ac, char **av)
{
	t_data	data;

	new_data(&data, av[0]);
	check_arg(ac, av, &data);
	parse(av[1], &data);
	new_mlx(&(data.mlx), av[0], &data);
	mlx_hook(data.mlx.win, 2, 1, key_press, &data);
	mlx_hook(data.mlx.win, 3, 2, key_release, &data);
	mlx_loop_hook(data.mlx.ptr, loop, &data);
	mlx_loop(data.mlx.ptr);
	ft_error(EMLX, &data);
}
