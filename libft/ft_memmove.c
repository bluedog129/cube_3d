/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:57:41 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/21 10:51:11 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_temp;
	unsigned char	*src_temp;

	dst_temp = (unsigned char *)dst;
	src_temp = (unsigned char *)src;
	if (dst_temp == src_temp)
		return (dst);
	if (dst_temp < src_temp)
		return (ft_memcpy(dst_temp, src_temp, len));
	else if (dst_temp > src_temp)
	{
		dst_temp += len;
		src_temp += len;
		while (len--)
			*(--dst_temp) = *(--src_temp);
		return (dst);
	}
	return (NULL);
}
