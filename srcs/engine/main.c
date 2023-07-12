
#include "cub3d.h"

int worldMap[14][33] =
{
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0},
  {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0}
};

//---------------------------



//---------------------------



//---------------------------

void	camera_setup(t_game_data *game_data)
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;

	pos.x = 1.5;
	pos.y = 5.5;
	// pos.y = 5.5;
	// y 축의 방향을 헛갈리지 말것...
	dir.x = 0.0;
	dir.y = -1.0;
	// cameraX에 곱해졌을때 어느축으로 움직이는지 생각해볼것..., -1 ~ 1 의 값은 곱하기위한 방향벡터였음...
	plane.x = 0.66;
	plane.y = 0;

	game_data->camera.pos.x = pos.x;
	game_data->camera.pos.y = pos.y;
	game_data->camera.dir.x = dir.x;
	game_data->camera.dir.y = dir.y;
	game_data->camera.plane.x = plane.x;
	game_data->camera.plane.y = plane.y;

	game_data->camera.move_speed = 0.04;
	game_data->camera.rotate_speed = 0.03;
}

//---------------------------



//---------------------------

void	load_textures(t_game_data	*game_data)
{
	char	*texture_path[4];
	int		i;

	texture_path[0] = "./res/west.xpm";
	texture_path[1] = "./res/south.xpm";
	texture_path[2] = "./res/east.xpm";
	texture_path[3] = "./res/north.xpm";
	i = 0;
	while (i < 4)
	{
		game_data->wall_texture[i].img_ptr = mlx_xpm_file_to_image(\
		game_data->mlx_ptr, texture_path[i], &game_data->wall_texture[i].\
		img_width, &game_data->wall_texture[i].img_height);
		game_data->wall_texture[i].img_addr = mlx_get_data_addr(\
		game_data->wall_texture[i].img_ptr, &game_data->wall_texture[i].\
		img_bpp, &game_data->wall_texture[i].img_line_len, \
		&game_data->wall_texture[i].img_endian);
		i++;
	}
}

//---------------------------

int	main()
{
	t_game_data	game_data;

	ft_bzero(&game_data, sizeof(t_game_data));
	camera_setup(&game_data);
	game_data.mlx_ptr = mlx_init();
	game_data.win_ptr = mlx_new_window(game_data.mlx_ptr, WIDTH, HEIGHT, \
	"raycast practice");

	load_textures(&game_data);

	draw_screen(&game_data);
	mlx_do_key_autorepeatoff(game_data.mlx_ptr);

	mlx_hook(game_data.win_ptr, 2, 1L << 0, my_key_pressed_hook, &game_data);
	mlx_hook(game_data.win_ptr, 3, 1L << 1, my_key_released_hook, &game_data);

	mlx_loop_hook(game_data.mlx_ptr, my_loop_hook, &game_data);

	mlx_loop(game_data.mlx_ptr);
}