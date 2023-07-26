/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hdoor_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:12 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:46:13 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_info_settup3(float eye_level, t_camera cam, \
t_raycaster rc, t_draw_info *draw_info)
{
	draw_info->line_len = (int)(HEIGHT / rc.perp_wall_dist);
	draw_info->draw_start = -draw_info->line_len / 2 + eye_level;
	if (draw_info->draw_start < 0)
		draw_info->draw_start = 0;
	draw_info->draw_end = draw_info->line_len / 2 + eye_level;
	if (draw_info->draw_end >= HEIGHT)
		draw_info->draw_end = HEIGHT - 1;
	draw_info->wall_x = cam.pos.y + rc.perp_wall_dist * rc.dir.y;
	draw_info->wall_x -= (int)draw_info->wall_x;
	draw_info->wall_x = 1 - draw_info->wall_x;
	draw_info->texture_pos.x = \
	(float)draw_info->target_texture->img_width * draw_info->wall_x;
	draw_info->texture_pos.y = \
	(draw_info->draw_start - eye_level + draw_info->line_len / 2) * \
	((float)draw_info->target_texture->img_height / draw_info->line_len);
}

void	dda_algorythm3_2(t_raycaster *rc, t_camera cam)
{
	float	temp;

	if (rc->side_dist.x > rc->side_dist.y)
	{
		rc->side = 1;
		temp = cam.pos.x + rc->side_dist.y * rc->dir.x;
		temp -= (int)temp;
		if (rc->dir.x > 0)
			temp = 1 - temp;
		if (temp > 0.5)
			rc->side = 2;
	}
	rc->side_dist.x -= rc->delta_dist.x / 2;
	rc->perp_wall_dist = rc->side_dist.x;
}

void	dda_algorythm3(char **map, t_raycaster *rc, t_camera *cam)
{
	while (1)
	{
		if (rc->side_dist.x < rc->side_dist.y)
		{
			rc->side_dist.x += rc->delta_dist.x;
			rc->map_check.x += rc->step.x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist.y += rc->delta_dist.y;
			rc->map_check.y += rc->step.y;
			rc->side = 1;
		}
		if (map[(int)rc->map_check.y][(int)rc->map_check.x] == '1')
		{
			rc->side = 2;
			return ;
		}
		else if (rc->side == 0 && map[(int)rc->map_check.y][\
		(int)rc->map_check.x] == 'd')
			break ;
	}
	dda_algorythm3_2(rc, *cam);
}

void	casting_through_hdoor(t_game_data *game_data, \
t_raycaster raycaster, t_img_data *screen, int screen_x)
{
	t_draw_info	draw_info;
	t_door		*target_door;

	raycaster.side_dist.x += raycaster.delta_dist.x / 2;
	dda_algorythm3(game_data->map_info->map_board, \
	&raycaster, &game_data->camera);
	if (raycaster.side == 2)
		return ;
	target_door = get_door(game_data->door_list, raycaster.map_check.x, \
	raycaster.map_check.y)->content;
	if (raycaster.side == 0 && target_door->state != CLOSE)
		casting_through_hdoor(game_data, raycaster, screen, screen_x);
	draw_info.target_texture = \
	&game_data->door_texture[(int)target_door->frame];
	draw_info_settup3(game_data->eye_level, game_data->camera, \
	raycaster, &draw_info);
	draw_vertical_line(draw_info.target_texture, screen, screen_x, &draw_info);
}

void	drawing_hdoors(t_game_data *game_data, t_img_data *screen, int screen_x)
{
	t_draw_info	draw_info;
	t_raycaster	raycaster;
	t_door		*target_door;

	raycaster_setup(&raycaster, game_data->camera, screen_x);
	dda_algorythm3(game_data->map_info->map_board, &raycaster, \
	&game_data->camera);
	if (raycaster.side != 2)
	{
		target_door = get_door(game_data->door_list, raycaster.map_check.x, \
		raycaster.map_check.y)->content;
		if (raycaster.side == 0 && target_door->state != CLOSE)
			casting_through_hdoor(game_data, raycaster, screen, screen_x);
		draw_info.target_texture = \
		&game_data->door_texture[(int)target_door->frame];
		draw_info_settup3(game_data->eye_level, game_data->camera, \
		raycaster, &draw_info);
		draw_vertical_line(draw_info.target_texture, screen, \
		screen_x, &draw_info);
	}
}
