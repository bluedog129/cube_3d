/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_event_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:01 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:46:02 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	serch_nearest_door(t_game_data *game_data, int screen_x, \
float *event_dist, t_door **target_door)
{
	t_raycaster	raycaster_v;
	t_raycaster	raycaster_h;

	raycaster_setup(&raycaster_v, game_data->camera, screen_x);
	dda_algorythm2(game_data->map_info->map_board, &raycaster_v, \
		&game_data->camera);
	raycaster_setup(&raycaster_h, game_data->camera, screen_x);
	dda_algorythm3(game_data->map_info->map_board, &raycaster_h, \
		&game_data->camera);
	if (raycaster_v.side != 2 && raycaster_v.perp_wall_dist <= *event_dist)
	{
		*target_door = get_door(game_data->door_list, raycaster_v.map_check.x, \
		raycaster_v.map_check.y)->content;
		*event_dist = raycaster_v.perp_wall_dist;
	}
	if (raycaster_h.side != 2 && raycaster_h.perp_wall_dist <= *event_dist)
	{
		*target_door = get_door(game_data->door_list, raycaster_h.map_check.x, \
		raycaster_h.map_check.y)->content;
		*event_dist = raycaster_h.perp_wall_dist;
	}
}

void	interact_doors(t_game_data *game_data)
{
	int			screen_x;
	float		event_dist;
	t_door		*target_door;

	event_dist = 1.5;
	target_door = NULL;
	screen_x = WIDTH / 4;
	while (screen_x < WIDTH / 2)
	{
		serch_nearest_door(game_data, screen_x, &event_dist, &target_door);
		screen_x++;
	}
	if (!target_door)
		return ;
	if (target_door->state == OPEN)
		target_door->state = CLOSING;
	else if (target_door->state == CLOSE)
		target_door->state = OPENING;
}
