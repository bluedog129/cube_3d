
#include "../../headers/cub3d.h"

static void	fill_floor_and_ceiling(t_img_data *screen, int floor, int ceiling)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				pixel_put_to_image(screen, x, y, floor);
			else
				pixel_put_to_image(screen, x, y, ceiling);
			x++;
		}
		y++;
	}
}

void	draw_screen(t_game_data *game_data)
{
	t_img_data	screen;

	screen.img_ptr = mlx_new_image(game_data->mlx_ptr, WIDTH, HEIGHT);
	screen.img_addr = mlx_get_data_addr(screen.img_ptr, &screen.img_bpp, \
	&screen.img_line_len, &screen.img_endian);
	fill_floor_and_ceiling(&screen, game_data->map_info->side_info->floor_rgb, \
	game_data->map_info->side_info->ceiling_rgb);
	drawing_walls(game_data, &screen);

	mlx_put_image_to_window(game_data->mlx_ptr, game_data->win_ptr, \
	screen.img_ptr, 0, 0);

	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 15, 0x000000, "mapX:");
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 70, 15, 0x000000, ft_itoa((int)game_data->camera.pos.x));
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 30, 0x000000, "mapY:");
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 70, 30, 0x000000, ft_itoa((int)game_data->camera.pos.y));

	mlx_destroy_image(game_data->mlx_ptr, screen.img_ptr);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	pixel_from_image(t_img_data *img, int x, int y)
{
	char	*dest;

	dest = img->img_addr + (y * img->img_line_len + x * (img->img_bpp / 8));
	return (*(unsigned int *)dest);
}

void	pixel_put_to_image(t_img_data *img, int x, int y, int color)
{
	char	*dest;

	dest = img->img_addr + (y * img->img_line_len + x * (img->img_bpp / 8));
	*(unsigned int *)dest = color;
}
