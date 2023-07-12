
#include "cub3d.h"

extern int worldMap[14][33];

int my_mouse_motion_hook(int x, int y, t_game_data *game_data)
{
	(void)game_data;
	(void)x;
	(void)y;
	if (x != 0 && y != 0)
	{
		mlx_mouse_move(game_data->mlx_ptr, game_data->win_ptr, 0, 0);
		printf("x: %d\ny: %d\n", x, y);
	}
	return (1);
}

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
	}
	draw_screen(game_data);
	return (0);
}
