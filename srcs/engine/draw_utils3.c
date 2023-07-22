/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:33 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:46:34 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dda_algorythm4(char **map, t_raycaster *rc)
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
			return (0);
		else if (rc->side == 1 && map[(int)rc->map_check.y][\
		(int)rc->map_check.x] == 'D')
			return (1);
		else if (rc->side == 0 && map[(int)rc->map_check.y][\
		(int)rc->map_check.x] == 'd')
			return (2);
	}
}

void	drawing_doors(t_game_data *game_data, t_img_data *screen)
{
	int			screen_x;
	int			door_type;
	t_raycaster	raycaster;

	screen_x = 0;
	while (screen_x < WIDTH)
	{
		raycaster_setup(&raycaster, game_data->camera, screen_x);
		door_type = dda_algorythm4(game_data->map_info->map_board, &raycaster);
		if (door_type == 1)
			drawing_vdoors(game_data, screen, screen_x);
		if (door_type == 2)
			drawing_hdoors(game_data, screen, screen_x);
		screen_x++;
	}
}
