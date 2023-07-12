
#include "../../headers/cub3d.h"

extern int worldMap[14][33];

int	my_key_pressed_hook(int keycode, t_game_data *game_data)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	if ((keycode == KEY_S) || (keycode == KEY_W))
		game_data->move_input.y += ((keycode == KEY_S) - (keycode == KEY_W));
	if ((keycode == KEY_D) || (keycode == KEY_A))
		game_data->move_input.x += ((keycode == KEY_D) - (keycode == KEY_A));
	if ((keycode == KEY_RIGHT) || (keycode == KEY_LEFT))
		game_data->rot_input += ((keycode == KEY_RIGHT) - \
		(keycode == KEY_LEFT));
	return (1);
}

int	my_key_released_hook(int keycode, t_game_data *game_data)
{
	if ((keycode == KEY_S) || (keycode == KEY_W))
		game_data->move_input.y -= ((keycode == KEY_S) - (keycode == KEY_W));
	if ((keycode == KEY_D) || (keycode == KEY_A))
		game_data->move_input.x -= ((keycode == KEY_D) - (keycode == KEY_A));
	if ((keycode == KEY_RIGHT) || (keycode == KEY_LEFT))
		game_data->rot_input -= ((keycode == KEY_RIGHT) - \
		(keycode == KEY_LEFT));
	return (1);
}

int	my_loop_hook(t_game_data *game_data)
{
	if (game_data->move_input.x != 0 || game_data->move_input.y != 0 \
	|| game_data->rot_input != 0)
	{
		move_event(game_data);
		draw_screen(game_data);
	}
	return (0);
}
