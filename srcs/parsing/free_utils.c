/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:38:42 by choihyojong       #+#    #+#             */
/*   Updated: 2023/07/10 22:39:08 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
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
	if (map_info->map_board != NULL)
		free_2d_arr(map_info->map_board);
	if (map_info->head_node != NULL)
	{
		if (map_info->head_node->next != NULL)
			free_lst_node(map_info->head_node->next);
	}
	if (map_info->head_node != NULL)
		free(map_info->head_node);
	if (parse_info->line != NULL)
		free(parse_info->line);
	if (parse_info->fd > 2)
		close(parse_info->fd);
	print_error(str);
}

void	finish_cub(t_map *map_info, t_parse_info *parse_info)
{
	if (map_info->side_info->north_tex != NULL)
		free(map_info->side_info->north_tex);
	if (map_info->side_info->south_tex != NULL)
		free(map_info->side_info->south_tex);
	if (map_info->side_info->west_tex != NULL)
		free(map_info->side_info->west_tex);
	if (map_info->side_info->east_tex != NULL)
		free(map_info->side_info->east_tex);
	if (map_info->map_board != NULL)
		free_2d_arr(map_info->map_board);
	if (map_info->head_node != NULL)
	{
		if (map_info->head_node->next != NULL)
			free_lst_node(map_info->head_node->next);
	}
	if (map_info->side_info != NULL)
		free(map_info->side_info);
	if (map_info->head_node != NULL)
		free(map_info->head_node);
	if (parse_info->line != NULL)
		free(parse_info->line);
	if (parse_info->fd > 2)
		close(parse_info->fd);
}
