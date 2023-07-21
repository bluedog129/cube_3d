
#include "cub3d.h"

void	draw_textes(t_game_data *game_data)
{
	char	*str;

	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 15, 0x000000, "mapX:");
	str = ft_itoa((int)game_data->camera.pos.x);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 70, 15, 0x000000, str);
	free(str);

	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 30, 0x000000, "mapY:");
	str = ft_itoa((int)game_data->camera.pos.y);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 70, 30, 0x000000, str);
	free(str);

	int mouse_x;
	int mouse_y;
	os_mouse_get_pos(game_data->mlx_ptr, game_data->win_ptr, &mouse_x, &mouse_y);

	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 45, 0x000000, "mouseX:");
	str = ft_itoa(mouse_x);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 80, 45, 0x000000, str);
	free(str);

	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 60, 0x000000, "mouseY:");
	str = ft_itoa(mouse_y);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 80, 60, 0x000000, str);
	free(str);

	char rschar[10];
	sprintf(rschar, "%.3f", game_data->camera.rotate_speed);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 75, 0x000000, "rotSpeed:");
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 110, 75, 0x000000, rschar);

	str = ft_itoa(game_data->rot_input.x);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 90, 0x000000, "rotInputX:");
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 110, 90, 0x000000, str);
	free(str);

	str = ft_itoa(game_data->rot_input.y);
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 5, 105, 0x000000, "rotInputY:");
	mlx_string_put(game_data->mlx_ptr, game_data->win_ptr, 110, 105, 0x000000, str);
	free(str);
}

void	rotate_vector2(t_vec2d *vec2, float degree)
{
	float	old_vec_x;
	float	radian;

	old_vec_x = (*vec2).x;
	radian = degree * M_PI / 180;
	(*vec2).x = (*vec2).x * cos(radian) - (*vec2).y * sin(radian);
	(*vec2).y = old_vec_x * sin(radian) + (*vec2).y * cos(radian);
}

int	is_passable(t_game_data *game_data, int x, int y)
{
	char	**map;
	t_door	*door;

	map = game_data->map_info->map_board;
	if (map[y][x] == '0')
		return (1);
	else if (map[y][x] == 'D' || map[y][x] == 'd')
	{
		door = get_door(game_data->door_list, x, y)->content;
		if (door->state == OPEN)
			return (1);
	}
	return (0);
}
