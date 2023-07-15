
#include "cub3d.h"

void	rotate_vector2(t_vec2d *vec2, float degree)
{
	float	old_vec_x;
	float	radian;

	old_vec_x = (*vec2).x;
	radian = degree * M_PI / 180;
	(*vec2).x = (*vec2).x * cos(radian) - (*vec2).y * sin(radian);
	(*vec2).y = old_vec_x * sin(radian) + (*vec2).y * cos(radian);
}

void	camera_setup(t_game_data *game_data)
{
	char	*dir_str;
	int		x;
	int		y;
	int		dir;

	game_data->camera.dir.y = -1.0;
	game_data->camera.plane.x = 0.66;
	game_data->camera.move_speed = 0.04;
	game_data->camera.rotate_speed = 0.014;
	game_data->eye_level = HEIGHT / 2;
	y = 0;
	dir_str = "NESW";
	while (y < game_data->map_info->height)
	{
		x = 0;
		while (x < game_data->map_info->width)
		{
			if (ft_strchr(dir_str, game_data->map_info->map_board[y][x]))
			{
				game_data->camera.pos.x = x + 0.5;
				game_data->camera.pos.y = y + 0.5;
				dir = 90 * (ft_strchr(dir_str, game_data->\
				map_info->map_board[y][x]) - dir_str);
				rotate_vector2(&game_data->camera.dir, dir);
				rotate_vector2(&game_data->camera.plane, dir);
				game_data->map_info->map_board[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	load_textures(t_game_data	*game_data)
{
	char	*texture_path[4];
	int		i;

	texture_path[0] = game_data->map_info->side_info->west_tex;
	texture_path[1] = game_data->map_info->side_info->south_tex;
	texture_path[2] = game_data->map_info->side_info->east_tex;
	texture_path[3] = game_data->map_info->side_info->north_tex;
	i = 0;
	while (i < 4)
	{
		game_data->wall_texture[i].img_ptr = mlx_xpm_file_to_image(\
		game_data->mlx_ptr, texture_path[i], &game_data->wall_texture[i].\
		img_width, &game_data->wall_texture[i].img_height);
		if (game_data->wall_texture[i].img_ptr == NULL)
			return (ERROR);
		game_data->wall_texture[i].img_addr = mlx_get_data_addr(\
		game_data->wall_texture[i].img_ptr, &game_data->wall_texture[i].\
		img_bpp, &game_data->wall_texture[i].img_line_len, \
		&game_data->wall_texture[i].img_endian);
		if (game_data->wall_texture[i].img_addr == NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	engine_main(t_map *map_info)
{
	t_game_data	game_data;

	ft_bzero(&game_data, sizeof(t_game_data));
	game_data.mlx_ptr = mlx_init();
	game_data.map_info = map_info;

	if (load_textures(&game_data) == ERROR)
	{
		printf("invalid resource path\n");
		return ;
	}

	camera_setup(&game_data);

	game_data.win_ptr = mlx_new_window(game_data.mlx_ptr, WIDTH, HEIGHT, \
	"raycast practice");

	os_mouse_move(game_data.mlx_ptr, game_data.win_ptr, WIDTH / 2, HEIGHT / 2);
	draw_screen(&game_data);

	mlx_do_key_autorepeatoff(game_data.mlx_ptr);
	mlx_mouse_hide(game_data.mlx_ptr, game_data.win_ptr);

	mlx_hook(game_data.win_ptr, 2, 1L << 0, my_key_pressed_hook, &game_data);
	mlx_hook(game_data.win_ptr, 3, 1L << 1, my_key_released_hook, &game_data);
	mlx_hook(game_data.win_ptr, 6, 1L << 6, my_mouse_motion_hook, &game_data);

	mlx_loop_hook(game_data.mlx_ptr, my_loop_hook, &game_data);

	mlx_loop(game_data.mlx_ptr);
}
