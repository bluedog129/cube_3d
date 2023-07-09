/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 22:00:08 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/05 09:47:27 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_temp;

	s_temp = (unsigned char *)s;
	while (n > 0)
	{
		if (*s_temp == (unsigned char)c)
			return (s_temp);
		s_temp++;
		n--;
	}
	return (NULL);
}
