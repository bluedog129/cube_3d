/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:47:05 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/29 18:23:50 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	camera_setup2(t_game_data *game_data, int x, int y)
{
	char	*dir_str;
	int		dir;

	dir_str = "NESW";
	if (ft_strchr(dir_str, game_data->map_info->map_board[y][x]))
	{
		game_data->camera.pos.x = x + 0.5;
		game_data->camera.pos.y = y + 0.5;
		dir = 90 * (ft_strchr(dir_str, game_data->\
		map_info->map_board[y][x]) - dir_str);
		rotate_vector2(&game_data->camera.dir, dir);
		rotate_vector2(&game_data->camera.plane, dir);
		game_data->map_info->map_board[y][x] = '0';
		return (1);
	}
	return (0);
}

void	camera_setup1(t_game_data *game_data)
{
	int		x;
	int		y;

	game_data->camera.dir.y = -1.0;
	game_data->camera.plane.x = 0.66;
	game_data->camera.move_speed = 0.04;
	game_data->camera.rotate_speed = 0.06;
	y = 0;
	while (y < game_data->map_info->height)
	{
		x = 0;
		while (x < game_data->map_info->width)
		{
			camera_setup2(game_data, x, y);
			x++;
		}
		y++;
	}
}

int	load_textures1(t_game_data	*game_data)
{
	char	*texture_path[4];
	int		i;

	texture_path[0] = game_data->map_info->side_info->west_tex;
	texture_path[1] = game_data->map_info->side_info->south_tex;
	texture_path[2] = game_data->map_info->side_info->east_tex;
	texture_path[3] = game_data->map_info->side_info->north_tex;
	i = 0;
	while (i < 4)
	{
		game_data->wall_texture[i].img_ptr = mlx_xpm_file_to_image(\
		game_data->mlx_ptr, texture_path[i], &game_data->wall_texture[i].\
		img_width, &game_data->wall_texture[i].img_height);
		if (game_data->wall_texture[i].img_ptr == NULL)
			return (ERROR);
		game_data->wall_texture[i].img_addr = mlx_get_data_addr(\
		game_data->wall_texture[i].img_ptr, &game_data->wall_texture[i].\
		img_bpp, &game_data->wall_texture[i].img_line_len, \
		&game_data->wall_texture[i].img_endian);
		if (game_data->wall_texture[i].img_addr == NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
