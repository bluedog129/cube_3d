/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   making_map_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:30:02 by choihyojong       #+#    #+#             */
/*   Updated: 2023/07/24 19:01:30 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	make_map_board(t_map *map_info, t_parse_info *parse_info)
{
	int	height;

	height = 0;
	map_info->map_board = (char **)malloc(sizeof(char *) * \
											(map_info->height + 1));
	if (map_info->map_board == NULL)
		exit_error("Error: board malloc failed\n", map_info, parse_info);
	while (height < map_info->height)
	{
		map_info->map_board[height] \
					= (char *)malloc(sizeof(char) * (map_info->width + 1));
		if (map_info->map_board[height] == NULL)
			exit_error("Error: board malloc failed\n", map_info, parse_info);
		map_info->map_board[height][map_info->width] = '\0';
		height++;
	}
	map_info->map_board[height] = 0;
}

static int	validate_all_round(t_map *map_info, char **map, int y, int x)
{
	int	y_idx;

	if (map[y][x] != '1' && map[y][x] != '*' && map[y][x] != ' ')
	{
		if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
			return (ERROR);
		y_idx = y;
		while (0 < --y_idx)
		{
			if (map[y_idx][x] == '1')
				break ;
			else if (map[y_idx][x] == ' ' || map[y_idx][x] == '*')
				return (ERROR);
		}
		y_idx = y;
		while (y_idx++ < map_info->height)
		{
			if (map[y_idx][x] == '1')
				return (SUCCESS);
			else if (map[y_idx][x] == ' ' || map[y_idx][x] == '*')
				return (ERROR);
		}
	}
	return (SUCCESS);
}

static void	validate_surrounded_wall(t_map *map_info, t_parse_info *parse_info)
{
	int	height;
	int	width;

	height = 0;
	while (height < map_info->height)
	{
		width = 0;
		while (width < map_info->width)
		{
			if (validate_edge_part(parse_info, map_info, \
									height, width) == ERROR)
				exit_error("Error: map is not surrounded by wall\n", \
							map_info, parse_info);
			else
			{
				if (validate_all_round(map_info, map_info->map_board, \
										height, width) == ERROR)
					exit_error("Error: map is not surrounded by wall\n", \
										map_info, parse_info);
			}
			width++;
		}
		height++;
	}
}

void	make_array_map(t_map *map_info, t_parse_info *parse_info)
{
	int			height;
	int			width;
	t_map_node	*curr_node;

	make_map_board(map_info, parse_info);
	height = 0;
	curr_node = map_info->head_node->next;
	while (curr_node)
	{
		width = 0;
		while (width < map_info->width)
		{
			if (width < (int)ft_strlen(curr_node->line))
				map_info->map_board[height][width] = curr_node->line[width];
			else
				map_info->map_board[height][width] = '*';
			width++;
		}
		height++;
		curr_node = curr_node->next;
	}
	free_lst_node(map_info->head_node);
	validate_surrounded_wall(map_info, parse_info);
}
