
#include "cub3d.h"

void	draw_vertical_line2(t_img_data *target_texture, t_img_data *img, \
int x, t_draw_info *draw_info)
{
	int			y;
	int			color;

	y = draw_info->draw_start;
	while (y <= draw_info->draw_end)
	{
		color = pixel_from_image(target_texture, draw_info->texture_pos.x, \
		draw_info->texture_pos.y + (64.0 / draw_info->line_len));
		if ((unsigned int)color != 0xff000000)
			pixel_put_to_image(img, x, y, color);
		draw_info->texture_pos.y += (64.0 / draw_info->line_len);
		y++;
	}
}

void	draw_info_settup2(float eye_level, t_camera cam, \
t_raycaster rc, t_draw_info *draw_info)
{
	draw_info->line_len = (int)(HEIGHT / rc.perp_wall_dist);
	draw_info->draw_start = -draw_info->line_len / 2 + eye_level;
	if (draw_info->draw_start < 0)
		draw_info->draw_start = 0;
	draw_info->draw_end = draw_info->line_len / 2 + eye_level;
	if (draw_info->draw_end >= HEIGHT)
		draw_info->draw_end = HEIGHT - 1;
	draw_info->wall_x = cam.pos.x + rc.perp_wall_dist * rc.dir.x;
	draw_info->wall_x -= (int)draw_info->wall_x;
	draw_info->texture_pos.x = 64.0 * draw_info->wall_x;
	draw_info->texture_pos.y = (draw_info->draw_start - eye_level + \
	draw_info->line_len / 2) * (64.0 / draw_info->line_len);
}

void	dda_algorythm2_2(t_raycaster *rc, t_camera cam)
{
	float	temp;

	if (rc->side_dist.x < rc->side_dist.y)
	{
		rc->side = 0;
		temp = cam.pos.y + rc->side_dist.x * rc->dir.y;
		temp -= (int)temp;
		if (rc->dir.y > 0)
			temp = 1 - temp;
		if (temp > 0.5)
			rc->side = 2;
	}
	rc->side_dist.y -= rc->delta_dist.y / 2;
	rc->perp_wall_dist = rc->side_dist.y;
}

void	dda_algorythm2(char **map, t_raycaster *rc, t_camera *cam)
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
		else if (rc->side == 1 && map[(int)rc->map_check.y][\
		(int)rc->map_check.x] == 'D')
			break ;
	}
	dda_algorythm2_2(rc, *cam);
}

void	raycaster_setup2(t_raycaster *rc, t_camera cam, int screen_x)
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
	rc->step.y = -1 * (rc->dir.y < 0) + 1 * (rc->dir.y > 0);
	if (rc->dir.x < 0)
		rc->side_dist.x = (cam.pos.x - rc->map_check.x) * rc->delta_dist.x;
	else
		rc->side_dist.x = (rc->map_check.x + 1 - cam.pos.x) * rc->delta_dist.x;
	if (rc->dir.y < 0)
		rc->side_dist.y = (cam.pos.y - rc->map_check.y) * rc->delta_dist.y;
	else
		rc->side_dist.y = (rc->map_check.y + 1 - cam.pos.y) * rc->delta_dist.y;
}

void	casting_through_door(t_game_data *game_data, \
t_raycaster raycaster, t_img_data *screen, int screen_x)
{
	t_draw_info	draw_info;
	t_door		*target_door;

	raycaster.side_dist.y += raycaster.delta_dist.y / 2;
	dda_algorythm2(game_data->map_info->map_board, \
	&raycaster, &game_data->camera);
	if (raycaster.side == 2)
		return ;
	draw_info_settup2(game_data->eye_level, game_data->camera, \
	raycaster, &draw_info);
	if (raycaster.side == 2)
		return ;
	target_door = get_door(game_data->door_list, raycaster.map_check.x, \
	raycaster.map_check.y)->content;
	if (raycaster.side == 1 && target_door->state != CLOSE)
		casting_through_door(game_data, raycaster, screen, screen_x);
	draw_vertical_line2(&game_data->door_texture[(int)target_door->frame], \
	screen, screen_x, &draw_info);
}

void	drawing_doors(t_game_data *game_data, t_img_data *screen)
{
	int			screen_x;
	t_draw_info	draw_info;
	t_raycaster	raycaster;
	t_door		*target_door;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		raycaster_setup2(&raycaster, game_data->camera, screen_x);
		dda_algorythm2(game_data->map_info->map_board, &raycaster, \
		&game_data->camera);
		if (raycaster.side != 2)
		{
			target_door = get_door(game_data->door_list, raycaster.map_check.x, \
			raycaster.map_check.y)->content;
			if (raycaster.side == 1 && target_door->state != CLOSE)
				casting_through_door(game_data, raycaster, screen, screen_x);
			draw_info_settup2(game_data->eye_level, game_data->camera, \
			raycaster, &draw_info);
			draw_vertical_line2(&game_data->door_texture[\
			(int)target_door->frame], screen, screen_x, &draw_info);
		}
		screen_x++;
	}
}
