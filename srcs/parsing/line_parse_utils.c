/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:53:54 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/09 16:56:14 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	open_file(char *cub_file)
{
	int	fd;

	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	return (fd);
}

int	check_line_empty(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

void	print_error(char *str)
{
	printf("%s", str);
	exit(ERROR);
}

void	exit_error(char *str, t_map *map_info, t_parse_info *parse_info)
{
	if (map_info->side_info->north_tex != NULL)
		free(map_info->side_info->north_tex);
	if (map_info->side_info->south_tex != NULL)
		free(map_info->side_info->south_tex);
	if (map_info->side_info->west_tex != NULL)
		free(map_info->side_info->west_tex);
	if (map_info->side_info->east_tex != NULL)
		free(map_info->side_info->east_tex);
	if (parse_info->fd > 2)
		close(parse_info->fd);
	print_error(str);
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
