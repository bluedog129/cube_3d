/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:07:02 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/05 10:02:31 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*s_temp;
	int		s_len;

	s_len = ft_strlen((char *)s) - 1;
	s_temp = (char *)s;
	if ((char)c == 0)
		return ((char *)(s_temp + s_len + 1));
	while (s_len >= 0)
	{
		if ((char)s_temp[s_len] == (char)c)
			return ((s_temp + s_len));
		s_len--;
	}
	return (NULL);
}
