#include "mlx.h"
#include <stdio.h>

#define WSX 600
#define WSY 450

#ifdef __linux__
# define KW
# define KA
# define KS
# define KD
#else
# define KW 13
# define KA 0
# define KS 1
# define KD 2
# define SH 257
# define ES 
#endif

typedef struct	s_mlx_struct
{
	void	*ptr;
	void	*win;
	int		k_press[512];
}				t_mlx_struct;

int	key_press_event(int keycode, t_mlx_struct *mlx)
{
	mlx->k_press[keycode] = 1;
	printf("Press:   %d\n", keycode);
	return 0;
}

int	key_release_event(int keycode, t_mlx_struct *mlx)
{
	mlx->k_press[keycode] = 0;
	printf("Release: %d\n", keycode);
	return 0;
}

int	loop_event(t_mlx_struct *mlx)
{
	static int	x=WSX/2-5, y=WSY/2-5, color=0x000000FF, cycle=0;
	int					speed, px, py, i, j;

	speed = mlx->k_press[SH] ? 2 : 1;
	if (mlx->k_press[KD]) x += speed;
	else if (mlx->k_press[KA]) x -= speed;
	if (mlx->k_press[KS]) y += speed;
	else if (mlx->k_press[KW]) y -= speed;

	switch (cycle)
	{
		case 0:
			color += 0x000100;
			if ((color & 0x00FF00) == 0x00FF00) cycle++;
			break;
		case 1:
			color -= 0x000001;
			if ((color & 0x0000FF) == 0) cycle++;
			break;
		case 2:
			color += 0x010000;
			if ((color & 0xFF0000) == 0xFF0000) cycle++;
			break;
		case 3:
			color -= 0x000100;
			if ((color & 0x00FF00) == 0) cycle++;
			break;
		case 4:
			color += 0x000001;
			if ((color & 0x0000FF) == 0x0000FF) cycle++;
			break;
		case 5:
			color -= 0x010000;
			if ((color & 0xFF0000) == 0) cycle = 0;
			break;
	}

	mlx_clear_window(mlx->ptr, mlx->win);
	for (i=0; i<10; i++)
		for (j=0; j<10; j++)
		{
			px = (x+i) % WSX;
			py = (y+j) % WSY;
			if (px<0) px+=WSX;
			if (py<0) py+=WSY;
			mlx_pixel_put(mlx->ptr, mlx->win, px, py, color);
		}
	return 0;
}

int	main()
{
	int				i, j;
	t_mlx_struct	mlx;

	for (i=0; i<512; i++) mlx.k_press[i] = 0;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WSX, WSY, "mlx test");
	mlx_do_key_autorepeatoff(mlx.ptr);
	
	for (i=0; i<10; i++)
		for (j=0; j<10; j++)
			mlx_pixel_put(mlx.ptr, mlx.win, WSX/2-5+i, WSY/2-5+j, 0x00FFFFFF);
	
	mlx_hook(mlx.win, 2, 1, key_press_event, &mlx);
	mlx_hook(mlx.win, 3, 2, key_release_event, &mlx);
	mlx_loop_hook(mlx.ptr, loop_event, &mlx);
	printf("test\n");
	
	mlx_loop(mlx.ptr);

	return (0);
}
