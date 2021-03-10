/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 15:34:31 by cbugnon           #+#    #+#             */
/*   Updated: 2021/03/10 14:34:19 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <fcntl.h>
#include <math.h>
#include <unistd.h>

#include "parse.h"
#include "render_bonus.h"
#include "event_bonus.h"
#include "struct.h"
#include "utils.h"
#include "mlx.h"

char		g_bmpheader[] =
{
	0x42, 0x4D,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00,
	0x00, 0x00,
	0x36, 0x00, 0x00, 0x00,
	0x28, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x01, 0x00,
	0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x13, 0x0B, 0x00, 0x00,
	0x13, 0x0B, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00
};

void		set_header(t_data *data)
{
	g_bmpheader[18] = data->scn.x & 0xFF;
	g_bmpheader[19] = data->scn.x >> 8 & 0xFF;
	g_bmpheader[20] = data->scn.x >> 16 & 0xFF;
	g_bmpheader[21] = data->scn.x >> 24 & 0xFF;
	g_bmpheader[22] = -data->scn.y & 0xFF;
	g_bmpheader[23] = -data->scn.y >> 8 & 0xFF;
	g_bmpheader[24] = -data->scn.y >> 16 & 0xFF;
	g_bmpheader[25] = -data->scn.y >> 24 & 0xFF;
	g_bmpheader[28] = data->scn.bpp;
}

void		save_bmp(t_data *data)
{
	int	fd;

	fd = open("./save.bmp", O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		ft_error(errno, data);
	set_header(data);
	if (write(fd, g_bmpheader, 54) < 0)
		ft_error(errno, data);
	cycle_angle(data);
	draw_sprites(data);
	if (write(fd, data->scn.addr, (int)ceil((double)(data->scn.x
				* data->scn.bpp) / 32) * data->scn.y * 4) < 0)
		ft_error(errno, data);
	if (close(fd) < 0)
		ft_error(errno, data);
	quit_cubed(data);
}

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
	data.save = check_arg(ac, av, &data);
	parse(av[1], &data);
	new_mlx(av[0], &data);
	if (data.save)
		save_bmp(&data);
	mlx_hook(data.win, 2, 1L << 0, key_press, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_hook(data.win, 17, 1L << 19, quit_cubed, &data);
	mlx_hook(data.win, 33, 0L, quit_cubed, &data);
	mlx_loop_hook(data.ptr, loop, &data);
	mlx_loop(data.ptr);
	ft_error(EMLX, &data);
}
