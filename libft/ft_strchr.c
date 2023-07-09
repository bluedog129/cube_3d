/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:38:46 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/05 09:50:51 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*s_temp;

	s_temp = (char *)s;
	while (*s_temp)
	{
		if (*s_temp == (char)c)
			return ((char *)s_temp);
		s_temp++;
	}
	if (*s_temp == (char)c)
		return ((char *)s_temp);
	return (NULL);
}
