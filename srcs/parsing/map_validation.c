/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:57:09 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/10 14:12:49 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	valid_map_characters(char *line, t_map *map_info, \
								t_parse_info *parse_info)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'E' && \
			line[i] != 'W' && line[i] != 'S' && line[i] != 'N' && \
			line[i] != ' ')
			exit_error("Error: invalid map characters", map_info, parse_info);
		else if (line[i] == 'N')
			parse_info->start_position_count++;
		else if (line[i] == 'S')
			parse_info->start_position_count++;
		else if (line[i] == 'W')
			parse_info->start_position_count++;
		else if (line[i] == 'E')
			parse_info->start_position_count++;
		i++;
	}
}

static int	validate_start_point(char start_point)
{
	if (start_point != '1')
		return (ERROR);
	return (SUCCESS);
}

static int	validate_end_point(char *line_split)
{
	int	idx;

	idx = 0;
	while (line_split[idx] != '\0' && line_split[idx] != '*')
		idx++;
	if (line_split[idx - 1] != '1')
		return (ERROR);
	return (SUCCESS);
}

static int	validate_map_lines(t_parse_info *parse_info, \
								t_map *map_info, int height)
{
	char	**line_split;
	int		idx;

	line_split = ft_split(map_info->map_board[height], ' ');
	if (line_split == NULL)
		exit_error("Error: split failed", map_info, parse_info);
	idx = -1;
	while (line_split[++idx])
	{
		if (line_split[idx][0] == '*')
			return (ERROR);
		if (validate_start_point(line_split[idx][0]) == ERROR)
		{
			free_2d_arr(line_split);
			return (ERROR);
		}
		if (validate_end_point(line_split[idx]) == ERROR)
		{
			free_2d_arr(line_split);
			return (ERROR);
		}
	}
	free_2d_arr(line_split);
	return (SUCCESS);
}

int	validate_edge_part(t_parse_info *parse_info, t_map *map_info, \
						int height, int width)
{
	if (height == 0 || height == map_info->height - 1)
	{
		if (map_info->map_board[height][width] != '1' && \
			map_info->map_board[height][width] != ' ' && \
			map_info->map_board[height][width] != '*')
			return (ERROR);
	}
	else
	{
		if (validate_map_lines(parse_info, map_info, height) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
