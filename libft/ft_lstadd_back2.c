/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:50:18 by yonghyle          #+#    #+#             */
/*   Updated: 2022/11/19 20:19:33 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back2(t_list **lst, t_list *new)
{
	t_list	*current;

	if (lst == NULL)
		return;
	if (*lst)
	{
		current = ft_lstlast2(*lst);
		current->next = new;
	}
	else
		*lst = new;
}