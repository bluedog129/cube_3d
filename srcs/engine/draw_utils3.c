
#include "cub3d.h"

void	darwing_wall(t_game_data *game_data, t_img_data *screen)
{
	// 맵 배열을 벗어나면 안됨
	// 미니맵 사이즈를 벗어나면 안됨
	// 기준점은 플레이어의 좌표 및 미니맵 화면 중앙
	int	y;
	int	x;

	// y = 0;
	// while (y < 100)
	// {
	// 	x = 0;
	// 	while (x < 100)
	// 	{
	// 		if (game_data->camera.pos.x - (x / 15) >= 0 && game_data->camera.pos.x + (x / 15) <= game_data->map_info->width)
	// 		{
	// 			if (game_data->camera.pos.y - (y / 15) >= 0 && game_data->camera.pos.y + (y / 15) <= game_data->map_info->height)
	// 			{
	// 				if (game_data->map_info->map_board[y / 15][x / 15] == '1')
	// 				{
	// 					pixel_put_to_image(screen, x, y, create_trgb(0, 0, 255, 0));
	// 				}
	// 			}
	// 		}
	// 		x++;
	// 	}
	// 	y++;
	// }

	y = -2;
	while (y <= 2)
	{
		if (game_data->camera.pos.y + y < 0 || game_data->camera.pos.y + y >= game_data->map_info->height)
		{
			y++;
			continue;
		}
		x = -2;
		while (x <= 2)
		{
			if (game_data->camera.pos.x + x < 0 || game_data->camera.pos.x + x >= game_data->map_info->width)
			{
				x++;
				continue;
			}
			// printf("game_data->camera.pos.y + y: %d\n", (int)(game_data->camera.pos.y + y));
			// printf("game_data->camera.pos.x + x: %d\n", (int)(game_data->camera.pos.x + x));
			// printf("game_data->map_info->map_board[(int)(game_data->camera.pos.y + y)][(int)(game_data->camera.pos.x + x)]: %c\n", game_data->map_info->map_board[(int)(game_data->camera.pos.y + y)][(int)(game_data->camera.pos.x + x)]);
			// printf("y: %d\n", y);
			// printf("x: %d\n", x);
			if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + y)][(int)(game_data->camera.pos.x + x)] == '1')
			{
				pixel_put_to_image(screen, x, y, create_trgb(0, 0, 255, 0));
				// printf("hi\n");
			}
			x++;
		}
		y++;
	}

	pixel_put_to_image(screen, 50, 50, create_trgb(0, 255, 0, 0));
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
