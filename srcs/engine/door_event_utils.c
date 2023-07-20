
#include "cub3d.h"

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
		else if (rc->side == 1 && map[(int)rc->map_check.y][(int)rc->map_check.x] == 'D')
		{
			if (rc->side_dist.x < rc->side_dist.y)
			{
				rc->side_dist.x += rc->delta_dist.x;
				rc->side = 0;
			}
			else
			{
				rc->side_dist.y += rc->delta_dist.y;
				rc->side = 1;
			}
			if (rc->side == 1)
			{
				rc->side_dist.y -= rc->delta_dist.y / 2;
				break ;
			}
			else
			{
				float temp;
				temp = cam->pos.y + (rc->side_dist.x - rc->delta_dist.x) * rc->dir.y;
				if (rc->dir.y > 0)
					temp = 64.0 - temp;
				temp -= (int)temp;

				if (temp < 0.5)
				{
					rc->side_dist.y += rc->delta_dist.y / 2;
					rc->side = 1;
					break ;
				}
				else
				{
					rc->side = 2;
					break ;
				}
			}
		}
	}
	if (rc->side == 0)
		rc->perp_wall_dist = rc->side_dist.x - rc->delta_dist.x;
	else
		rc->perp_wall_dist = rc->side_dist.y - rc->delta_dist.y;
}

void	raycaster_setup3(t_raycaster *rc, t_camera cam, int screen_x)
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

void interact_doors(t_game_data *game_data)
{
	int			screen_x;
	t_raycaster	raycaster;
	float		event_dist;
	t_door		*target_door;

	event_dist = 10;
	target_door = NULL;
	screen_x = 160;
	while (screen_x < 320)
	{
		raycaster_setup3(&raycaster, game_data->camera, screen_x);
		dda_algorythm3(game_data->map_info->map_board, &raycaster, &game_data->camera);
		if (raycaster.side == 2)
		{
			screen_x++;
			continue ;
		}
		if (event_dist > raycaster.perp_wall_dist && raycaster.perp_wall_dist <= 1.5)
		{
			event_dist = raycaster.perp_wall_dist;
			target_door = get_door(game_data->door_list, raycaster.map_check.x, raycaster.map_check.y)->content;
		}
		screen_x++;
	}
	// printf("dist: %f\n", event_dist);
	if (!target_door)
		return ;
	if (target_door->state == OPEN)
		target_door->state = CLOSING;
	else if (target_door->state == CLOSE)
		target_door->state = OPENING;
}
