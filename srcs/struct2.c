/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbugnon <cbugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 15:24:48 by cbugnon           #+#    #+#             */
/*   Updated: 2020/09/08 06:33:42 by cbugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "utils.h"
#include "struct.h"

void		img_null(t_img *tex)
{
	tex->ptr = NULL;
	tex->x = 0;
	tex->y = 0;
	tex->addr = NULL;
	tex->bpp = 0;
	tex->sl = 0;
	tex->endian = 0;
}

void		free_img(t_img *img, t_data *data)
{
	if (data && data->ptr && img->ptr)
		mlx_destroy_image(data->ptr, img->ptr);
	img_null(img);
}

void		new_tex(int i, t_img *tex, t_data *data)
{
	if (!(tex->ptr = mlx_xpm_file_to_image(data->ptr, data->path_tex[i],
			&tex->x, &tex->y)))
		ft_error(ETEXTURE, data);
	if (!(tex->addr = mlx_get_data_addr(tex->ptr, &tex->bpp, &tex->sl,
			&tex->endian)))
		ft_error(ETEXTURE, data);
}

void		new_img(t_img *scn, int x, int y, t_data *data)
{
	scn->x = x;
	scn->y = y;
	if (!(scn->ptr = mlx_new_image(data->ptr, scn->x, scn->y)))
		ft_error(ETEXTURE, data);
	if (!(scn->addr = mlx_get_data_addr(scn->ptr, &scn->bpp, &scn->sl,
			&scn->endian)))
		ft_error(ETEXTURE, data);
}

void			new_pos(t_pos *pos, size_t x, size_t y)
{
	pos->x = x;
	pos->y = y;
}
