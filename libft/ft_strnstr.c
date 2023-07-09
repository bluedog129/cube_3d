/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:04:49 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/27 21:42:03 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_equal(char *haystack, char *needle, size_t len)
{
	int		i;
	size_t	lefted_len;	

	i = 0;
	lefted_len = len;
	while ((haystack[i] == needle[i]) && lefted_len > 0)
	{
		if (needle[i + 1] == '\0')
			return (1);
		i++;
		lefted_len--;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0' && len > 0)
	{
		if (*haystack == *needle)
		{
			if (ft_check_equal((char *)haystack, (char *)needle, len))
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
