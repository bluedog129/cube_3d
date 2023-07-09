/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:33:02 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/21 17:12:41 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen((char *)src);
	i = 0;
	if (dstsize <= src_len)
	{
		while (i + 1 < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
	}
	else
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (dstsize != 0)
		dst[i] = 0;
	return (src_len);
}
