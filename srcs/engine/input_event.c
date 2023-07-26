/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:47:08 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:47:09 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
}

static void	move_horizontal(t_game_data *game_data)
{
	float	move_speed;
	t_vec2d	rot_dir;
	t_vec2d	old_pos;
	t_vec2d	new_pos;

	move_speed = game_data->camera.move_speed;
	old_pos.x = game_data->camera.pos.x;
	old_pos.y = game_data->camera.pos.y;
	rot_dir.x = game_data->camera.dir.x * cos(90 * M_PI / 180) - \
	game_data->camera.dir.y * sin(90 * M_PI / 180);
	rot_dir.y = game_data->camera.dir.x * sin(90 * M_PI / 180) + \
	game_data->camera.dir.y * cos(90 * M_PI / 180);
	new_pos.x = old_pos.x + rot_dir.x * move_speed * game_data->move_input.x;
	new_pos.y = old_pos.y + rot_dir.y * move_speed * game_data->move_input.x;
	if (is_passable(game_data, new_pos.x, old_pos.y))
		game_data->camera.pos.x += rot_dir.x * move_speed * \
		game_data->move_input.x;
	if (is_passable(game_data, old_pos.x, new_pos.y))
		game_data->camera.pos.y += rot_dir.y * move_speed * \
		game_data->move_input.x;
}

static void	move_vertical(t_game_data *game_data)
{
	t_vec2d	old_pos;
	t_vec2d	new_pos;
	float	move_speed;

	move_speed = game_data->camera.move_speed;
	old_pos.x = game_data->camera.pos.x;
	old_pos.y = game_data->camera.pos.y;
	new_pos.x = old_pos.x - game_data->camera.dir.x * move_speed * \
	game_data->move_input.y;
	new_pos.y = old_pos.y - game_data->camera.dir.y * move_speed * \
	game_data->move_input.y;
	if (is_passable(game_data, old_pos.x, new_pos.y))
		game_data->camera.pos.y -= game_data->camera.dir.y * move_speed * \
		game_data->move_input.y;
	if (is_passable(game_data, new_pos.x, old_pos.y))
		game_data->camera.pos.x -= game_data->camera.dir.x * move_speed * \
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
}
