/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:09:11 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/06 14:17:54 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_temp;
	unsigned char	*src_temp;

	dst_temp = (unsigned char *)dst;
	src_temp = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (0);
	while (n)
	{
		*dst_temp = *src_temp;
		dst_temp++;
		src_temp++;
		n--;
	}
	return (dst);
}
