/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:47:00 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:47:01 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	my_mouse_motion_hook(int x, int y, t_game_data *game_data)
{
	(void)x;
	(void)y;
	(void)game_data;
	if (x != WIDTH / 2 || y != HEIGHT / 2)
	{
		game_data->rot_input.x = (x - (WIDTH / 2)) * 0.3;
		game_data->rot_input.y = (y - (HEIGHT / 2)) * -100;
	}
	return (1);
}

int	my_key_pressed_hook(int keycode, t_game_data *game_data)
{
	if (keycode == KEY_ESC)
		exit_cub3d(game_data, 0);
	if ((keycode == KEY_S) || (keycode == KEY_W))
		game_data->move_input.y += ((keycode == KEY_S) - (keycode == KEY_W));
	if ((keycode == KEY_D) || (keycode == KEY_A))
		game_data->move_input.x += ((keycode == KEY_D) - (keycode == KEY_A));
	if ((keycode == KEY_RIGHT) || (keycode == KEY_LEFT))
		game_data->rot_input.x += ((keycode == KEY_RIGHT) - \
		(keycode == KEY_LEFT));
	if (keycode == KEY_SPACEBAR)
		interact_doors(game_data);
	return (1);
}

int	my_key_released_hook(int keycode, t_game_data *game_data)
{
	if ((keycode == KEY_RIGHT_SQUARE_BRACKET) || \
	(keycode == KEY_LEFT_SQUARE_BRACKET))
	{
		game_data->camera.rotate_speed += (\
		(keycode == KEY_RIGHT_SQUARE_BRACKET) - \
		(keycode == KEY_LEFT_SQUARE_BRACKET)) * 0.002;
		if (game_data->camera.rotate_speed < 0)
			game_data->camera.rotate_speed = 0;
	}
	if ((keycode == KEY_S) || (keycode == KEY_W))
		game_data->move_input.y -= ((keycode == KEY_S) - (keycode == KEY_W));
	if ((keycode == KEY_D) || (keycode == KEY_A))
		game_data->move_input.x -= ((keycode == KEY_D) - (keycode == KEY_A));
	if ((keycode == KEY_RIGHT) || (keycode == KEY_LEFT))
		game_data->rot_input.x -= ((keycode == KEY_RIGHT) - \
		(keycode == KEY_LEFT));
	return (1);
}

int	my_loop_hook(t_game_data *game_data)
{
	if (game_data->move_input.x != 0 || game_data->move_input.y != 0 \
	|| game_data->rot_input.x != 0 || game_data->rot_input.y != 0)
	{
		move_event(game_data);
	}
	ft_lstiter(game_data->door_list, door_update);
	draw_screen(game_data);
	os_mouse_move(game_data->mlx_ptr, \
	game_data->win_ptr, WIDTH / 2, HEIGHT / 2);
	return (0);
}
