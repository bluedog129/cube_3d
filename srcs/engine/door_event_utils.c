
#include "cub3d.h"

void	interact_doors(t_game_data *game_data)
{
	int			screen_x;
	t_raycaster	raycaster;
	float		event_dist;
	t_door		*target_door;

	event_dist = 10;
	target_door = NULL;
	screen_x = WIDTH / 4;
	while (screen_x < WIDTH / 2)
	{
		raycaster_setup(&raycaster, game_data->camera, screen_x);
		dda_algorythm2(game_data->map_info->map_board, &raycaster, \
		&game_data->camera);
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
	if (!target_door)
		return ;
	if (target_door->state == OPEN)
		target_door->state = CLOSING;
	else if (target_door->state == CLOSE)
		target_door->state = OPENING;
}
