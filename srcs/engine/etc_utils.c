/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   etc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:54 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:48:37 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_cub3d(t_game_data *game_data, int is_err)
{
	int	i;

	i = 0;
	while (i < 4 && game_data->wall_texture[i].img_ptr)
	{
		mlx_destroy_image(game_data->mlx_ptr, game_data->wall_texture[i].\
		img_ptr);
		i++;
	}
	i = 0;
	while (i < 6 && game_data->door_texture[i].img_ptr)
	{
		mlx_destroy_image(game_data->mlx_ptr, game_data->door_texture[i].\
		img_ptr);
		i++;
	}
	if (game_data->win_ptr)
		mlx_destroy_window(game_data->mlx_ptr, game_data->win_ptr);
	finish_cub(game_data->map_info, game_data->parse_info);
	exit(is_err);
}

void	rotate_vector2(t_vec2d *vec2, float degree)
{
	float	old_vec_x;
	float	radian;

	old_vec_x = (*vec2).x;
	radian = degree * M_PI / 180;
	(*vec2).x = (*vec2).x * cos(radian) - (*vec2).y * sin(radian);
	(*vec2).y = old_vec_x * sin(radian) + (*vec2).y * cos(radian);
}

int	is_passable(t_game_data *game_data, int x, int y)
{
	char	**map;

	map = game_data->map_info->map_board;
	if (map[y][x] == '0')
		return (1);
	return (0);
}
