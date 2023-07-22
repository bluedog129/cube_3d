/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_list_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:46:06 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/22 18:46:07 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_update(void *content)
{
	t_door	*door;

	door = content;
	if (door->state == OPENING)
	{
		if (door->frame < 5.0)
			door->frame += 0.2;
		else
			door->state = OPEN;
	}
	else if (door->state == CLOSING)
	{
		if (door->frame > 0.0)
			door->frame -= 0.2;
		else
			door->state = CLOSE;
	}
}

t_list	*get_door(t_list *door_list, int x, int y)
{
	t_door	*door;

	while (door_list)
	{
		door = door_list->content;
		if (door->pos.x == x && door->pos.y == y)
			return (door_list);
		door_list = door_list->next;
	}
	return (NULL);
}

t_list	*new_door(int x, int y)
{
	t_list	*new;
	t_door	*content;

	new = NULL;
	content = malloc(sizeof(t_door));
	if (content)
	{
		memset(content, 0, sizeof(t_door));
		content->pos.x = x;
		content->pos.y = y;
		new = ft_lstnew(content);
		if (!new)
			free(content);
	}
	return (new);
}

int	get_door_list(t_map *map_info, t_list **door_list)
{
	t_list	*new;
	int		y;
	int		x;

	y = 0;
	while (y < map_info->height)
	{
		x = 0;
		while (x < map_info->width)
		{
			if (map_info->map_board[y][x] == 'd' || \
			map_info->map_board[y][x] == 'D')
			{
				new = new_door(x, y);
				if (!new)
					return (0);
				ft_lstadd_back2(door_list, new);
			}
			x++;
		}
		y++;
	}
	return (1);
}
