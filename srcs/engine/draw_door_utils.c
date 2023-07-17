
#include "cub3d.h"

void	draw_vertical_line2(t_game_data *game_data, t_img_data *img, \
int x, t_draw_info *draw_info)
{
	t_img_data	*target_texture;
	int			y;
	int			color;

	target_texture = &game_data->wall_texture[draw_info->texture_idx];
	y = draw_info->draw_start; // 이 부분을 밖으로 빼면 모듈화가 될것같기도...?
	while (y <= draw_info->draw_end)
	{
		// color = pixel_from_image(target_texture, draw_info->texture_pos.x, \
		// draw_info->texture_pos.y + (64.0 / draw_info->line_len));
		color = create_trgb(0, 0, 0, 0);
		pixel_put_to_image(img, x, y, color);
		draw_info->texture_pos.y += (64.0 / draw_info->line_len);
		y++;
	}
}

void	draw_info_settup2(float eye_level, t_camera cam, t_raycaster rc, t_draw_info *draw_info)
{
	draw_info->line_len = (int)(HEIGHT / rc.perp_wall_dist);
	draw_info->draw_start = -draw_info->line_len / 2 + eye_level;
	if (draw_info->draw_start < 0)
		draw_info->draw_start = 0;
	draw_info->draw_end = draw_info->line_len / 2 + eye_level;
	if (draw_info->draw_end >= HEIGHT)
		draw_info->draw_end = HEIGHT - 1;
	if (rc.side == 0)
	{
		draw_info->wall_x = cam.pos.y + rc.perp_wall_dist * rc.dir.y;
		if (rc.dir.x < 0)
			draw_info->wall_x = 64.0 - draw_info->wall_x;
		draw_info->wall_x -= (int)draw_info->wall_x;
	}
	else
	{
		draw_info->wall_x = cam.pos.x + rc.perp_wall_dist * rc.dir.x;
		if (rc.dir.y > 0)
			draw_info->wall_x = 64.0 - draw_info->wall_x;
		draw_info->wall_x -= (int)draw_info->wall_x;
	}
	draw_info->texture_pos.x = 64.0 * draw_info->wall_x;
	draw_info->texture_pos.y = (draw_info->draw_start - eye_level + \
	draw_info->line_len / 2) * (64.0 / draw_info->line_len);
}

void	dda_algorythm2(char **map, t_raycaster *rc)
{
	float temp_check_x = rc->map_check.x;
	float temp_check_y = rc->map_check.y;
	float temp_side_x = rc->side_dist.x;
	float temp_side_y = rc->side_dist.y;
	float temp_delta_x = rc->delta_dist.x;
	float temp_delta_y = rc->delta_dist.y;
	// int	check_mod;

	// check_mod = 0; // 0: wall 1: door
	while (1)
	{
		// printf("---\nmod: %d\ny: %f\nx: %f\n", check_mod, rc->map_check.y, rc->map_check.x);
		// if (!(rc->map_check.y - (int)rc->map_check.y) && map[(int)rc->map_check.y][(int)rc->map_check.x] == '1')
		// {
		// 	rc->side = 2;
		// 	return ;
		// }

		// if (rc->side_dist.x < rc->side_dist.y)
		// {
		// 	rc->side_dist.x += rc->delta_dist.x;
		// 	rc->map_check.x += rc->step.x;
		// 	rc->side = 0;
		// }
		// else
		// {
		// 	rc->side_dist.y += rc->delta_dist.y;
		// 	rc->map_check.y += rc->step.y;
		// 	rc->side = 1;
		// }
		// check_mod = (check_mod == 0);

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
			// if ((rc->side == 0 && rc->map_check.x - (int)rc->map_check.x == 0) || (rc->side == 1 && rc->map_check.y - (int)rc->map_check.y == 0))
			// {
				// printf("rc->map_check.x: %f\n", rc->map_check.x);
				// printf("rc->map_check.y: %f\n", rc->map_check.y);
				// printf("map[(int)rc->map_check.y][(int)rc->map_check.x]: %c\n", map[(int)rc->map_check.y][(int)rc->map_check.x]);
				rc->side = 2;
				return ;
			// }
		}
		else if (map[(int)rc->map_check.y][(int)rc->map_check.x] == 'D')
		{
			// if ((rc->side == 0 && rc->map_check.x - (int)rc->map_check.x == 0.5) || (rc->side == 1 && rc->map_check.y - (int)rc->map_check.y == 0.5))
				break;
		}
	}
	printf("=================================\n");
	// printf("rc->side: %d\n", rc->side);
	// printf("step.x: %f\n", rc->step.x);
	// printf("step.y: %f\n", rc->step.y);
	// printf("(int)rc->map_check.x: %d\n", (int)rc->map_check.x);
	// printf("(int)rc->map_check.y: %d\n", (int)rc->map_check.y);
	printf("rc->map_check.x: %f\n", rc->map_check.x);
	printf("rc->map_check.y: %f\n", rc->map_check.y);
	printf("map[(int)rc->map_check.y][(int)rc->map_check.x]: %c\n", map[(int)rc->map_check.y][(int)rc->map_check.x]);

	while (temp_check_x != rc->map_check.x && temp_check_y != rc->map_check.y)
	{
		printf("============\n");
		printf("tempX: %f\n", temp_check_x);
		printf("tempy: %f\n", temp_check_y);
		printf("board[y][x]: %c\n", map[(int)temp_check_y][(int)temp_check_x]);

		if (temp_side_x < temp_side_y)
		{
			temp_side_x += temp_delta_x;
			temp_check_x += rc->step.x;
		}
		else
		{
			temp_side_y += temp_delta_y;
			temp_check_y += rc->step.y;
		}
	}
	printf("============1\n");
	printf("tempX: %f\n", temp_check_x);
	printf("tempy: %f\n", temp_check_y);
	printf("board[y][x]: %c\n", map[(int)temp_check_y][(int)temp_check_x]);

	if (rc->side == 0)
	{
		rc->perp_wall_dist = rc->side_dist.x - rc->delta_dist.x;
		// rc->perp_wall_dist += rc->delta_dist.x;
	}
	else
	{
		rc->perp_wall_dist = rc->side_dist.y - rc->delta_dist.y;
		// rc->perp_wall_dist += rc->delta_dist.y;
	}

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
	rc->step.y = -1 * (rc->dir.y < 0) + (rc->dir.y > 0);
	if (rc->dir.x < 0)
		rc->side_dist.x = (cam.pos.x - rc->map_check.x) * rc->delta_dist.x;
	else
		rc->side_dist.x = (rc->map_check.x + 1 - cam.pos.x) * rc->delta_dist.x;
	if (rc->dir.y < 0)
	{
		rc->side_dist.y = (cam.pos.y - rc->map_check.y) * rc->delta_dist.y;
	}
	else
	{
		rc->side_dist.y = (rc->map_check.y + 1 - cam.pos.y) * rc->delta_dist.y;
	}

	// rc->camera_x = 2 * screen_x / (float)WIDTH - 1;
	// rc->dir.x = cam.dir.x + cam.plane.y * rc->camera_x;
	// rc->dir.y = cam.dir.y + cam.plane.y * rc->camera_x;
	// rc->map_check.x = (int)cam.pos.x;
	// rc->map_check.y = (int)cam.pos.y;
	// ft_bzero(&rc->step, sizeof(t_vec2d));
	// rc->delta_dist.x = fabsf(1 / rc->dir.y);
	// rc->delta_dist.y = fabsf(1 / rc->dir.y);
	// rc->step.x = -1 * (rc->dir.y < 0) + (rc->dir.x > 0);
	// rc->step.y = -1 * (rc->dir.y < 0) + (rc->dir.y > 0);
	// if (rc->dir.y < 0)
	// 	rc->side_dist.x = (cam.pos.y - rc->map_check.y) * rc->delta_dist.y;
	// else
	// 	rc->side_dist.x = (rc->map_check.y + 1 - cam.pos.y) * rc->delta_dist.y;
	// if (rc->dir.y < 0)
	// 	rc->side_dist.y = (cam.pos.y - rc->map_check.y + 0.5) * rc->delta_dist.y;
	// else
	// 	rc->side_dist.y = (rc->map_check.y + 1 - cam.pos.y + 0.5) * rc->delta_dist.y;
}

void drawing_doors(t_game_data *game_data, t_img_data *screen)
{
	int			screen_x;
	t_draw_info	draw_info;
	t_raycaster	raycaster;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		raycaster_setup2(&raycaster, game_data->camera, screen_x);
		dda_algorythm2(game_data->map_info->map_board, &raycaster);
		if (raycaster.side == 2)
		{
			screen_x++;
			continue ;
		}
		draw_info_settup2(game_data->eye_level, game_data->camera, raycaster, &draw_info);
		draw_info.texture_idx = raycaster.side;
		if ((raycaster.side == 0 && raycaster.dir.x < 0) || \
		(raycaster.side == 1 && raycaster.dir.y > 0))
			draw_info.texture_idx += 2;
		draw_vertical_line2(game_data, screen, screen_x, &draw_info);
		screen_x++;
	}
}