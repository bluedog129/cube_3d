
#include "cub3d.h"

static void	rotate_vertical(t_game_data *game_data)
{
	float	limit;

	limit = HEIGHT / 8;
	game_data->eye_level += game_data->rot_input.y * game_data->camera.rotate_speed;
	if (game_data->eye_level < -limit)
		game_data->eye_level = -limit;
	else if (game_data->eye_level >= HEIGHT + limit)
		game_data->eye_level = HEIGHT + limit - 1;

	if (fabsf(game_data->rot_input.y) > 0.05)
		game_data->rot_input.y /= 2;
	else
		game_data->rot_input.y = 0;	
}

static void	rotate_horizontal(t_game_data *game_data)
{
	float	rotate_speed;
	float	old_dir_x;
	float	old_plane_x;

	rotate_speed = game_data->camera.rotate_speed;
	old_dir_x = game_data->camera.dir.x;
	game_data->camera.dir.x = game_data->camera.dir.x * cos(rotate_speed * \
	game_data->rot_input.x) - game_data->camera.dir.y * sin(rotate_speed * \
	game_data->rot_input.x);
	game_data->camera.dir.y = old_dir_x * sin(rotate_speed * \
	game_data->rot_input.x) + game_data->camera.dir.y * cos(rotate_speed * \
	game_data->rot_input.x);
	old_plane_x = game_data->camera.plane.x;
	game_data->camera.plane.x = game_data->camera.plane.x * \
	cos(rotate_speed * game_data->rot_input.x) - game_data->camera.plane.y * \
	sin(rotate_speed * game_data->rot_input.x);
	game_data->camera.plane.y = old_plane_x * sin(rotate_speed * \
	game_data->rot_input.x) + game_data->camera.plane.y * cos(rotate_speed * \
	game_data->rot_input.x);
	if (fabsf(game_data->rot_input.x) > 0.05)
		game_data->rot_input.x /= 2;
	else
		game_data->rot_input.x = 0;
}

static void	move_horizontal(t_game_data *game_data)
{
	char	**map;
	float	move_speed;
	t_vec2d	rot_dir;

	map = game_data->map_info->map_board;
	move_speed = game_data->camera.move_speed;
	rot_dir.x = game_data->camera.dir.x * cos(90 * M_PI / 180) - \
	game_data->camera.dir.y * sin(90 * M_PI / 180);
	rot_dir.y = game_data->camera.dir.x * sin(90 * M_PI / 180) + \
	game_data->camera.dir.y * cos(90 * M_PI / 180);
	if (map[(int)game_data->camera.pos.y][(int)(game_data->camera.pos.x \
	+ rot_dir.x * move_speed * game_data->move_input.x)] == '0')
		game_data->camera.pos.x += rot_dir.x * move_speed * \
		game_data->move_input.x;
	if (map[(int)(game_data->camera.pos.y + rot_dir.y * move_speed * \
	game_data->move_input.x)][(int)(game_data->camera.pos.x)] == '0')
		game_data->camera.pos.y += rot_dir.y * move_speed * \
		game_data->move_input.x;
}

static void	move_vertical(t_game_data *game_data)
{
	char	**map;
	float	move_speed;

	map = game_data->map_info->map_board;
	move_speed = game_data->camera.move_speed;
	if (map[(int)game_data->camera.pos.y][(int)(game_data->camera.pos.x - \
	game_data->camera.dir.x * move_speed * game_data->move_input.y)] == '0')
		game_data->camera.pos.x -= game_data->camera.dir.x * move_speed * \
		game_data->move_input.y;
	if (map[(int)(game_data->camera.pos.y - game_data->camera.dir.y * \
	move_speed * game_data->move_input.y)][(int)(game_data->camera.pos.x)] == \
	'0')
		game_data->camera.pos.y -= game_data->camera.dir.y * move_speed * \
		game_data->move_input.y;
}

void	move_event(t_game_data *game_data)
{
	if (game_data->move_input.y != 0)
		move_vertical(game_data);
	if (game_data->move_input.x != 0)
		move_horizontal(game_data);
	if (game_data->rot_input.x != 0)
		rotate_horizontal(game_data);
	if (game_data->rot_input.y != 0)
		rotate_vertical(game_data);
}
