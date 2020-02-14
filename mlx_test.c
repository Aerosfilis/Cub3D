#include "mlx.h"

#define WSX 600
#define WSY 450

int	main()
{
	void	*mlx_ptr = mlx_init();
	void	*win_ptr = mlx_new_window(mlx_ptr, WSX, WSY, "mlx test");

	mlx_loop(mlx_ptr);
	(void)win_ptr;

	return (0);
}
