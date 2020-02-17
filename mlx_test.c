#include "mlx.h"
#include <stdio.h>
#include <limits.h>
#include <time.h>

#define WSX 600
#define WSY 450
#define MAX_KEY 512
#define TARGET_FPS 120

#ifdef __linux__
# define KW 119
# define KA 97
# define KS 115
# define KD 100
# define SH 65505
# define ES 65307
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
	void			*ptr;
	void			*win;
	unsigned short	k_press[USHRT_MAX];
}				t_mlx_struct;

int				get_fps()
{
	static clock_t	last=0;
	clock_t			current=clock(), total=CLOCKS_PER_SEC/(current-last);
	last = current;
	(void)total;
	return total;
}


int	key_press_event(int keycode, t_mlx_struct *mlx)
{
	printf("Press:   %d\n", keycode);
	mlx->k_press[keycode] = 1;
	if (keycode == KW && mlx->k_press[KS]) mlx->k_press[KS] = 2;
	else if (keycode == KS && mlx->k_press[KW]) mlx->k_press[KW] = 2;
	else if (keycode == KA && mlx->k_press[KD]) mlx->k_press[KD] = 2;
	else if (keycode == KD && mlx->k_press[KA]) mlx->k_press[KA] = 2;
	return 0;
}

int	key_release_event(int keycode, t_mlx_struct *mlx)
{
	printf("Release: %d\n", keycode);
	if (keycode > USHRT_MAX || keycode < 0) return 0;
	mlx->k_press[keycode] = 0;
	if (keycode == KW && mlx->k_press[KS]) mlx->k_press[KS] = 1;
	else if (keycode == KS && mlx->k_press[KW]) mlx->k_press[KW] = 1;
	else if (keycode == KA && mlx->k_press[KD]) mlx->k_press[KD] = 1;
	else if (keycode == KD && mlx->k_press[KA]) mlx->k_press[KA] = 1;
	return 0;
}

int	loop_event(t_mlx_struct *mlx)
{
	static int			x=WSX/2-5, y=WSY/2-5, color=0x000000FF, cycle=0;
	static clock_t		last=0;
	int					speed, px, py, i, j, fps;
	clock_t				current;
	char				fps_str[] = "   ";

	speed = mlx->k_press[SH] ? (double)(200/TARGET_FPS)*2 : (200/TARGET_FPS);
	if (mlx->k_press[KD] == 1) x += speed;
	else if (mlx->k_press[KA] == 1) x -= speed;
	if (mlx->k_press[KS] == 1) y += speed;
	else if (mlx->k_press[KW] == 1) y -= speed;

	//*
	switch (cycle)
	{
		case 0:
			color += 0x000100 * (200/TARGET_FPS);
			if ((color & 0x00FE00) == 0x00FE00) cycle++;
			break;
		case 1:
			color -= 0x000001 * (200/TARGET_FPS);
			if ((color & 0x0000FE) == 0) cycle++;
			break;
		case 2:
			color += 0x010000 * (200/TARGET_FPS);
			if ((color & 0xFE0000) == 0xFE0000) cycle++;
			break;
		case 3:
			color -= 0x000100 * (200/TARGET_FPS);
			if ((color & 0x00FE00) == 0) cycle++;
			break;
		case 4:
			color += 0x000001 * (200/TARGET_FPS);
			if ((color & 0x0000FE) == 0x0000FE) cycle++;
			break;
		case 5:
			color -= 0x010000 * (200/TARGET_FPS);
			if ((color & 0xFE0000) == 0) cycle = 0;
			break;
	}
	//*/(void)cycle;

	current = clock();
	while (CLOCKS_PER_SEC/(current-last) > TARGET_FPS) current = clock();
	last = current;

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
	//*
	fps = get_fps();
	i = (fps>99) + 1;
	while (i>=0)
	{
		fps_str[i] = fps%10 + 48;
		fps /= 10;
		i--;
	}
	mlx_string_put(mlx->ptr, mlx->win, 2, 11, 0xFFFFFF, fps_str);
	//*/
	return 0;
}

int	main()
{
	int				i, j;
	t_mlx_struct	mlx;
	
	get_fps();
	for (i=0; i<USHRT_MAX; i++) mlx.k_press[i] = 0;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WSX, WSY, "mlx test");
	mlx_do_key_autorepeaton(mlx.ptr);
	
	for (i=0; i<10; i++)
		for (j=0; j<10; j++)
			mlx_pixel_put(mlx.ptr, mlx.win, WSX/2-5+i, WSY/2-5+j, 0x00FFFFFF);
	
	mlx_hook(mlx.win, 2, 1, key_press_event, &mlx);
	mlx_hook(mlx.win, 3, 2, key_release_event, &mlx);
	mlx_loop_hook(mlx.ptr, loop_event, &mlx);
	
	mlx_loop(mlx.ptr);

	return (0);
}
