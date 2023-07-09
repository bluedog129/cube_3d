/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:05:09 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/23 21:58:06 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	temp_s1 = (unsigned char *)s1;
	temp_s2 = (unsigned char *)s2;
	while ((*temp_s1 != '\0' || *temp_s2 != '\0') && n > 0)
	{
		if (*temp_s1 < *temp_s2)
			return (-1);
		else if (*temp_s1 > *temp_s2)
			return (1);
		n--;
		temp_s1++;
		temp_s2++;
	}
	return (0);
}
