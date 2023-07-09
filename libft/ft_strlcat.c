/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 19:27:40 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/23 13:05:42 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int		dst_len;
	unsigned int		src_len;
	unsigned int		cat_size;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	cat_size = dstsize - dst_len - 1;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (*dst)
		dst++;
	if (dstsize > dst_len)
	{
		while ((cat_size) && *src != '\0')
		{
			*dst = *src;
			dst++;
			src++;
			cat_size--;
		}
		*dst = '\0';
	}
	return (dst_len + src_len);
}
