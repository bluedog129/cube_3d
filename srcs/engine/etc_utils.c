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

void	draw_textes2(t_game_data *game_data)
{
	void	*mp;
	void	*wp;
	char	*str;
	char	rschar[10];

	mp = game_data->mlx_ptr;
	wp = game_data->win_ptr;
	sprintf(rschar, "%.3f", game_data->camera.rotate_speed);
	mlx_string_put(mp, wp, 5, 75, 0x000000, "rotSpeed:");
	mlx_string_put(mp, wp, 110, 75, 0x000000, rschar);
	str = ft_itoa(game_data->rot_input.x);
	mlx_string_put(mp, wp, 5, 90, 0x000000, "rotInputX:");
	mlx_string_put(mp, wp, 110, 90, 0x000000, str);
	free(str);
	str = ft_itoa(game_data->rot_input.y);
	mlx_string_put(mp, wp, 5, 105, 0x000000, "rotInputY:");
	mlx_string_put(mp, wp, 110, 105, 0x000000, str);
	free(str);
}

void	draw_textes1(t_game_data *game_data)
{
	void	*mp;
	void	*wp;
	char	*str;
	t_vec2d	mouse_pos;

	mp = game_data->mlx_ptr;
	wp = game_data->win_ptr;
	mlx_string_put(mp, wp, 5, 15, 0x000000, "mapX:");
	str = ft_itoa((int)game_data->camera.pos.x);
	mlx_string_put(mp, wp, 70, 15, 0x000000, str);
	free(str);
	mlx_string_put(mp, wp, 5, 30, 0x000000, "mapY:");
	str = ft_itoa((int)game_data->camera.pos.y);
	mlx_string_put(mp, wp, 70, 30, 0x000000, str);
	free(str);
	os_mouse_get_pos(mp, wp, (int *)&mouse_pos.x, (int *)&mouse_pos.y);
	mlx_string_put(mp, wp, 5, 45, 0x000000, "mouseX:");
	str = ft_itoa(mouse_pos.x);
	mlx_string_put(mp, wp, 80, 45, 0x000000, str);
	free(str);
	mlx_string_put(mp, wp, 5, 60, 0x000000, "mouseY:");
	str = ft_itoa(mouse_pos.y);
	mlx_string_put(mp, wp, 80, 60, 0x000000, str);
	free(str);
	draw_textes2(game_data);
}

void	exit_cub3d(t_game_data *game_data)
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
	ft_lstclear(&game_data->door_list, free);
	if (game_data->win_ptr)
		mlx_destroy_window(game_data->mlx_ptr, game_data->win_ptr);
	finish_cub(game_data->map_info, game_data->parse_info);
	exit(EXIT_SUCCESS);
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
	t_door	*door;

	map = game_data->map_info->map_board;
	if (map[y][x] == '0')
		return (1);
	else if (map[y][x] == 'D' || map[y][x] == 'd')
	{
		door = get_door(game_data->door_list, x, y)->content;
		if (door->state == OPEN)
			return (1);
	}
	return (0);
}
