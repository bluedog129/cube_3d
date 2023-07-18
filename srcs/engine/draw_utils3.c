
#include "cub3d.h"

void	darwing_wall(t_game_data *game_data, t_img_data *screen)
{
	// 맵 배열을 벗어나면 안됨
	// 미니맵 사이즈를 벗어나면 안됨
	// 기준점은 플레이어의 좌표 및 미니맵 화면 중앙
	// int	y;
	// int	x;

	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			int map_div = 7;
			int factor = 100 / map_div;
			int check_x = x / factor;
			int check_y = y / factor;

			t_vec2d draw_vec;

			check_x -= map_div / 2;
			check_y -= map_div / 2;

			if (game_data->camera.pos.x + check_x < 0 || game_data->camera.pos.x + check_x >= game_data->map_info->width ||
			game_data->camera.pos.y + check_y < 0 || game_data->camera.pos.y + check_y >= game_data->map_info->height)
				continue;
			
			if (check_x == 0 && check_y == 0)
				pixel_put_to_image(screen, x, y, create_trgb(0, 255, 0, 0));
			else if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + check_y)][(int)(game_data->camera.pos.x + check_x)] != '0')
			{
				draw_vec.x = x - 50;
				draw_vec.y = y - 50;
				rotate_vector2(&draw_vec, atan2f(game_data->camera.dir.y, game_data->camera.dir.x) * 180 / M_PI * -1 - 90);
				draw_vec.x += 50;
				draw_vec.y += 50;
				if (draw_vec.x < 0 || draw_vec.x >= 100 || draw_vec.y < 0 || draw_vec.y >= 100)
					continue;
				if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + check_y)][(int)(game_data->camera.pos.x + check_x)] == '1')
					pixel_put_to_image(screen, draw_vec.x, draw_vec.y, create_trgb(0, 0, 255, 0));
				else if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + check_y)][(int)(game_data->camera.pos.x + check_x)] == 'D')
					pixel_put_to_image(screen, draw_vec.x, draw_vec.y, create_trgb(0, 255, 255, 102));
			}
		}
	}

	// pixel_put_to_image(screen, 50, 50, create_trgb(0, 255, 0, 0));
}

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

	darwing_wall(game_data, &screen);

	mlx_put_image_to_window(game_data->mlx_ptr, game_data->win_ptr, screen.img_ptr, 530, 10);

	mlx_destroy_image(game_data->mlx_ptr, screen.img_ptr);
}
