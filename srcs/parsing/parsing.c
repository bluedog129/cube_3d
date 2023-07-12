/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:28:09 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/10 20:01:56 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_line_by_line(t_map *map_info, t_parse_info *parse_info)
{
	char	*line;

	while (1)
	{
		line = get_next_line(parse_info->fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		parse_info->line_type = check_type(line);
		if (parse_info->line_type == SIDE_TEXTURE)
			validate_texture(line, map_info, parse_info);
		else if (parse_info->line_type == RGB)
			validate_rgb(line, map_info, parse_info);
		else if (parse_info->line_type == MAP)
			validate_map(line, map_info, parse_info);
		else if (parse_info->line_type == EMPTY_LINE && map_info->height > 0)
			exit_error("Error: Invalid empty_line map\n", map_info, parse_info);
		free(line);
	}
	if (validate_all_lines(parse_info) == ERROR)
		exit_error("Error: Invalid all line validation\n", map_info, parse_info);
}

void	parse_cub_file(char *cub_file, t_map *map_info, \
									t_parse_info *parse_info)
{
	initialize(cub_file, map_info, parse_info);
	parse_line_by_line(map_info, parse_info);
	if (parse_info->fd > 2)
		close(parse_info->fd);
}
