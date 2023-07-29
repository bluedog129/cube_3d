/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getting_side_info_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 19:53:46 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/10 15:43:01 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_texture_path(char **texture_info, t_map *map_info, \
						t_parse_info *parse_info)
{
	if (ft_strcmp("NO", texture_info[0]) == 0)
	{
		map_info->side_info->north_tex = ft_strdup(texture_info[1]);
		parse_info->north_tex_count++;
	}
	else if (ft_strcmp("SO", texture_info[0]) == 0)
	{
		map_info->side_info->south_tex = ft_strdup(texture_info[1]);
		parse_info->south_tex_count++;
	}
	else if (ft_strcmp("WE", texture_info[0]) == 0)
	{
		map_info->side_info->west_tex = ft_strdup(texture_info[1]);
		parse_info->west_tex_count++;
	}
	else if (ft_strcmp("EA", texture_info[0]) == 0)
	{
		map_info->side_info->east_tex = ft_strdup(texture_info[1]);
		parse_info->east_tex_count++;
	}
	else
		return (ERROR);
	return (TRUE);
}

int	get_rgb(char *rgb_val, t_map *map_info, t_parse_info *parse_info)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	rgb = ft_split(rgb_val, ',');
	if (rgb == NULL)
		exit_error("Error: map allocate fail\n", map_info, parse_info);
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		free_2d_arr(rgb);
		exit_error("Error: Invalid RGB\n", map_info, parse_info);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_2d_arr(rgb);
		exit_error("Error: Invalid RGB\n", map_info, parse_info);
	}
	free_2d_arr(rgb);
	return (r * 256 * 256 + g * 256 + b);
}
