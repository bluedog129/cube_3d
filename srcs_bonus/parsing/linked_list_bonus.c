/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 12:30:17 by choihyojong       #+#    #+#             */
/*   Updated: 2023/07/10 15:47:03 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_lstadd_back(t_map_node *lst, t_map_node *_new)
{
	t_map_node	*back_pos;

	if (lst == NULL)
	{
		lst = _new;
		return ;
	}
	back_pos = ft_lstlast(lst);
	back_pos -> next = _new;
}

t_map_node	*ft_lstlast(t_map_node *lst)
{
	t_map_node	*dummy;

	dummy = lst;
	while (dummy != NULL && ((dummy -> next) != NULL))
		dummy = dummy -> next;
	return (dummy);
}

void	free_lst_node(t_map_node *head)
{
	t_map_node	*remove;

	if (head == NULL)
		return ;
	while (head->next != NULL)
	{
		remove = head->next;
		head->next = head->next->next;
		free(remove->line);
		free(remove);
	}
}
