/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:48 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/29 19:46:55 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	dest_event_hook(t_game_data *game_data)
{
	exit_cub3d(game_data, 0);
	return (0);
}

static void	first_settup(t_game_data	*game_data)
{
	draw_screen(game_data);
	mlx_do_key_autorepeatoff(game_data->mlx_ptr);
	mlx_hook(game_data->win_ptr, 2, 1L << 0, my_key_pressed_hook, game_data);
	mlx_hook(game_data->win_ptr, 3, 1L << 1, my_key_released_hook, game_data);
	mlx_hook(game_data->win_ptr, 17, 0, dest_event_hook, game_data);
	mlx_loop_hook(game_data->mlx_ptr, my_loop_hook, game_data);
}

void	engine_main(t_map *map_info, t_parse_info *parse_info)
{
	t_game_data	*game_data;

	game_data = malloc(sizeof(t_game_data));
	ft_bzero(game_data, sizeof(t_game_data));
	game_data->mlx_ptr = mlx_init();
	game_data->map_info = map_info;
	game_data->parse_info = parse_info;
	if (load_textures1(game_data) == ERROR)
	{
		printf("invalid resource path\n");
		exit_cub3d(game_data, 1);
		return ;
	}
	camera_setup1(game_data);
	game_data->win_ptr = mlx_new_window(game_data->mlx_ptr, WIDTH, HEIGHT, \
	"raycast practice");
	first_settup(game_data);
	mlx_loop(game_data->mlx_ptr);
}
