
#include "cub3d.h"

void	filling_background(t_img_data *screen)
{
	int	x;
	int	y;

	y = 0;
	while (y < 100)
	{
		x = 0;
		while (x < 100)
		{
			if (((x == 0 || x == 99) && (y >= 0 && y < 100)) || \
			((x >= 0 && x < 100) && (y == 0 || y == 99)))
				pixel_put_to_image(screen, x, y, create_trgb(0, 0, 255, 0));
			else
				pixel_put_to_image(screen, x, y, create_trgb(100, 0, 40, 0));
			x++;
		}
		y++;
	}
}

void	drawing_minimap(t_game_data *game_data)
{
	t_img_data	screen;

	screen.img_ptr = mlx_new_image(game_data->mlx_ptr, 100, 100);
	screen.img_addr = mlx_get_data_addr(screen.img_ptr, &screen.img_bpp, \
	&screen.img_line_len, &screen.img_endian);

	filling_background(&screen);

	mlx_put_image_to_window(game_data->mlx_ptr, game_data->win_ptr, screen.img_ptr, 530, 10);

	mlx_destroy_image(game_data->mlx_ptr, screen.img_ptr);
}
