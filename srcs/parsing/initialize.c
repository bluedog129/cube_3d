/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:24:34 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/18 14:53:19 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize(char *cub_file, t_map *map_info, t_parse_info *parse_info)
{
	ft_memset((void *)map_info, 0, sizeof(t_map));
	ft_memset((void *)parse_info, 0, sizeof(t_parse_info));
	parse_info->fd = open_file(cub_file);
	if (parse_info->fd < 2)
		print_error("Error: Invalid file\n");
	map_info->side_info = (t_side_info *)malloc(sizeof(t_side_info));
	ft_memset((void *)map_info->side_info, 0, sizeof(t_side_info));
	map_info->head_node = (t_map_node *)malloc(sizeof(t_map_node));
	if (map_info->head_node == NULL)
		exit_error("Error: map allocate fail", map_info, parse_info);
	map_info->head_node->line = NULL;
	map_info->head_node->next = NULL;
}
