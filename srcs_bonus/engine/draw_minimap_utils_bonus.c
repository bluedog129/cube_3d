/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:17 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/29 19:54:33 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	draw_minimap3(t_game_data *game_data, t_img_data *screen, \
t_vec2d draw_pos, \
t_vec2d check_pos)
{
	t_vec2d	wall_draw_pos;

	wall_draw_pos.x = draw_pos.x - 50;
	wall_draw_pos.y = draw_pos.y - 50;
	rotate_vector2(&wall_draw_pos, atan2f(game_data->camera.dir.y, \
	game_data->camera.dir.x) * 180 / M_PI * -1 - 90);
	wall_draw_pos.x += 50;
	wall_draw_pos.y += 50;
	if (wall_draw_pos.x < 0 || wall_draw_pos.x >= 100 || \
	wall_draw_pos.y < 0 || wall_draw_pos.y >= 100)
		return ;
	if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + \
	check_pos.y)][(int)(game_data->camera.pos.x + check_pos.x)] == '1')
		pixel_put_to_image(screen, wall_draw_pos.x, wall_draw_pos.y, \
		create_trgb(0, 0, 255, 0));
	else if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + \
	check_pos.y)][(int)(game_data->camera.pos.x + check_pos.x)] == 'D')
		pixel_put_to_image(screen, wall_draw_pos.x, wall_draw_pos.y, \
		create_trgb(0, 255, 255, 102));
	else if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + \
	check_pos.y)][(int)(game_data->camera.pos.x + check_pos.x)] == 'd')
		pixel_put_to_image(screen, wall_draw_pos.x, wall_draw_pos.y, \
		create_trgb(0, 255, 255, 102));
}

static void	draw_minimap2(t_game_data *game_data, t_img_data *screen, \
t_vec2d draw_pos)
{
	int		map_div;
	int		factor;
	t_vec2d	check_pos;

	map_div = 7;
	factor = 100 / map_div;
	check_pos.x = (int)draw_pos.x / factor - map_div / 2;
	check_pos.y = (int)draw_pos.y / factor - map_div / 2;
	if (game_data->camera.pos.x + check_pos.x < 0 || game_data->camera.pos.x + \
	check_pos.x >= game_data->map_info->width || game_data->camera.pos.y + \
	check_pos.y < 0 || game_data->camera.pos.y + check_pos.y >= \
	game_data->map_info->height)
		return ;
	if (check_pos.x == 0 && check_pos.y == 0)
		pixel_put_to_image(screen, draw_pos.x, draw_pos.y, \
		create_trgb(0, 255, 0, 0));
	else if (game_data->map_info->map_board[(int)(game_data->camera.pos.y + \
	check_pos.y)][(int)(game_data->camera.pos.x + check_pos.x)] != '0')
		draw_minimap3(game_data, screen, draw_pos, check_pos);
}

static void	draw_minimap1(t_game_data *game_data, t_img_data *screen)
{
	t_vec2d	draw_pos;

	memset(&draw_pos, 0, sizeof(t_vec2d));
	while (draw_pos.y < 100)
	{
		draw_pos.x = 0;
		while (draw_pos.x < 100)
		{
			draw_minimap2(game_data, screen, draw_pos);
			draw_pos.x++;
		}
		draw_pos.y++;
	}
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
	draw_minimap1(game_data, &screen);
	mlx_put_image_to_window(game_data->mlx_ptr, game_data->win_ptr, \
	screen.img_ptr, WIDTH - 110, 10);
	mlx_destroy_image(game_data->mlx_ptr, screen.img_ptr);
}
