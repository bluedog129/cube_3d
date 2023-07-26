/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:28 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:46:28 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_vertical_line(t_img_data *target_texture, t_img_data *img, \
int x, t_draw_info *draw_info)
{
	int			y;
	int			color;

	y = draw_info->draw_start;
	while (y < draw_info->draw_end)
	{
		color = pixel_from_image(target_texture, draw_info->texture_pos.x, \
		draw_info->texture_pos.y);
		if ((unsigned int)color != 0xff000000)
			pixel_put_to_image(img, x, y, color);
		draw_info->texture_pos.y += ((float)target_texture->img_height / \
		draw_info->line_len);
		y++;
	}
}

void	draw_info_settup(float eye_level, t_camera cam, \
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
	if (rc.dir.x < 0)
		draw_info->wall_x = 1 - draw_info->wall_x;
	if (rc.side % 2)
	{
		draw_info->wall_x = cam.pos.x + rc.perp_wall_dist * rc.dir.x;
		draw_info->wall_x -= (int)draw_info->wall_x;
		if (rc.dir.y > 0)
			draw_info->wall_x = 1 - draw_info->wall_x;
	}
	draw_info->texture_pos.x = \
	(float)draw_info->target_texture->img_width * draw_info->wall_x;
	draw_info->texture_pos.y = \
	(draw_info->draw_start - eye_level + draw_info->line_len / 2) * \
	((float)draw_info->target_texture->img_height / draw_info->line_len);
}

void	dda_algorythm(char **map, t_raycaster *rc)
{
	while (map[(int)rc->map_check.y][(int)rc->map_check.x] != '1')
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
	}
	if (rc->side == 0)
		rc->perp_wall_dist = rc->side_dist.x - rc->delta_dist.x;
	else
		rc->perp_wall_dist = rc->side_dist.y - rc->delta_dist.y;
}

void	raycaster_setup(t_raycaster *rc, t_camera cam, int screen_x)
{
	rc->camera_x = 2 * screen_x / (float)WIDTH - 1;
	rc->dir.x = cam.dir.x + cam.plane.x * rc->camera_x;
	rc->dir.y = cam.dir.y + cam.plane.y * rc->camera_x;
	rc->map_check.x = (int)cam.pos.x;
	rc->map_check.y = (int)cam.pos.y;
	ft_bzero(&rc->step, sizeof(t_vec2d));
	rc->delta_dist.x = fabsf(1 / rc->dir.x);
	rc->delta_dist.y = fabsf(1 / rc->dir.y);
	rc->step.x = -1 * (rc->dir.x < 0) + (rc->dir.x > 0);
	rc->step.y = -1 * (rc->dir.y < 0) + (rc->dir.y > 0);
	if (rc->dir.x < 0)
		rc->side_dist.x = (cam.pos.x - rc->map_check.x) * rc->delta_dist.x;
	else
		rc->side_dist.x = (rc->map_check.x + 1 - cam.pos.x) * rc->delta_dist.x;
	if (rc->dir.y < 0)
		rc->side_dist.y = (cam.pos.y - rc->map_check.y) * rc->delta_dist.y;
	else
		rc->side_dist.y = (rc->map_check.y + 1 - cam.pos.y) * rc->delta_dist.y;
}

void	drawing_walls(t_game_data *game_data, t_img_data *screen)
{
	int			screen_x;
	t_draw_info	draw_info;
	t_raycaster	raycaster;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		raycaster_setup(&raycaster, game_data->camera, screen_x);
		dda_algorythm(game_data->map_info->map_board, &raycaster);
		draw_info.texture_idx = raycaster.side;
		if ((raycaster.side == 0 && raycaster.dir.x < 0) || \
		(raycaster.side == 1 && raycaster.dir.y > 0))
			draw_info.texture_idx += 2;
		draw_info.target_texture = &game_data->\
		wall_texture[draw_info.texture_idx];
		draw_info_settup(game_data->eye_level, game_data->camera, \
		raycaster, &draw_info);
		draw_vertical_line(&game_data->wall_texture[draw_info.texture_idx], \
		screen, screen_x, &draw_info);
		screen_x++;
	}
}
