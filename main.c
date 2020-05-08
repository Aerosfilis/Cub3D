#include "srcs/parse.h"
#include "srcs/struct.h"
#include <sys/types.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	t_data data;

	new_data(&data, av[0]);
	parse(av[1], &data);
	printf("Res: %d %d\n", data.res.x, data.res.y);
	
	printf("\nNO: %s\n", data.path_tex[TEX_NO]);
	printf("SO: %s\n", data.path_tex[TEX_SO]);
	printf("WE: %s\n", data.path_tex[TEX_WE]);
	printf("EA: %s\n", data.path_tex[TEX_EA]);
	printf("S: %s\n", data.path_tex[TEX_SPRITE]);

	printf("\nC: %d\n", data.col_ceil);
	printf("F: %d\n", data.col_floor);

	printf("Map: %d %d\n", data.smap.x, data.smap.y);
	for (int i=0; i < data.smap.y; i++)
	{
		for (int j=0; j < data.smap.x; j++)
			printf("%d", data.map[j][i]);
		printf("\n");
	}
	free_data(&data);
}
