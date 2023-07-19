/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:13:06 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/18 17:41:32 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_texture(char *tex_line, t_map *map_info, \
						t_parse_info *parse_info)
{
	char	**texture_info;

	texture_info = ft_split(tex_line, ' ');
	if (texture_info == NULL)
	{
		exit_error("Error: Invalid texture\n", map_info, parse_info);
	}
	if (texture_info[0] == NULL || texture_info[1] == NULL || \
		texture_info[2] != NULL)
	{
		exit_error("Error: Invalid texture\n", map_info, parse_info);
	}
	if (get_texture_path(texture_info, map_info, parse_info) == ERROR)
	{
		exit_error("Error: Invalid texture\n", map_info, parse_info);
	}
	free_2d_arr(texture_info);
}

void	validate_rgb(char *tex_line, t_map *map_info, t_parse_info *parse_info)
{
	char	**rgb_info;

	rgb_info = ft_split(tex_line, ' ');
	if (rgb_info == NULL)
	{
		exit_error("Error: Invalid RGB\n", map_info, parse_info);
	}
	if (rgb_info[0] == NULL || rgb_info[1] == NULL || \
		rgb_info[2] != NULL)
	{
		exit_error("Error: Invalid RGB\n", map_info, parse_info);
	}
	if (ft_strcmp("F", rgb_info[0]) == 0)
	{
		map_info->side_info->floor_rgb = get_rgb(rgb_info[1], \
											map_info, parse_info);
		parse_info->floor_rgb_count++;
	}
	if (ft_strcmp("C", rgb_info[0]) == 0)
	{
		map_info->side_info->ceiling_rgb = get_rgb(rgb_info[1], \
											map_info, parse_info);
		parse_info->ceiling_rgb_count++;
	}
	free_2d_arr(rgb_info);
}

void	validate_map(char *map_line, t_map *map_info, t_parse_info *parse_info)
{
	t_map_node	*map_node;

	valid_map_characters(map_line, map_info, parse_info);
	map_node = (t_map_node *)malloc(sizeof(t_map_node));
	if (map_node == NULL)
		exit_error("Error: map allocate fail\n", map_info, parse_info);
	map_node->line = ft_strdup(map_line);
	if (map_node->line == NULL)
	{
		free(map_node);
		exit_error("Error: fail get line to node\n", map_info, parse_info);
	}
	map_node->next = NULL;
	ft_lstadd_back(map_info->head_node, map_node);
	map_info->height++;
	if (map_info->width <= (int)ft_strlen(map_line))
		map_info->width = (int)ft_strlen(map_line);
}

int	validate_all_lines(t_parse_info *parse_info)
{
	if (parse_info->north_tex_count == 1 && parse_info->south_tex_count == 1 \
	&& parse_info->west_tex_count == 1 && parse_info->east_tex_count == 1 \
	&& parse_info->floor_rgb_count == 1 && parse_info->ceiling_rgb_count == 1)
	{
		if (parse_info->start_position_count == 1)
			return (SUCCESS);
	}
	return (ERROR);
}

int	check_type(char *line)
{
	if (check_line_empty(line) == TRUE)
		return (EMPTY_LINE);
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || \
			ft_strncmp(line, "SO ", 3) == 0 || \
			(ft_strncmp(line, "WE ", 3) == 0) || \
			ft_strncmp(line, "EA ", 3) == 0)
		return (SIDE_TEXTURE);
	else if (ft_strncmp(line, "F ", 2) == 0 || \
			ft_strncmp(line, "C ", 2) == 0)
		return (RGB);
	return (MAP);
}
