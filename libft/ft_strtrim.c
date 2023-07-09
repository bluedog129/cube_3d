/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:55:38 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/03 12:03:37 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_address_check(const char *str_end, \
int result_len, const char *s1)
{
	if (str_end < s1)
		result_len = 0;
	else
		result_len = (str_end - s1 + 1);
	return (result_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			set_len;
	int			s1_len;
	int			result_len;
	char		*str_end;
	char		*result;

	set_len = ft_strlen((char *)set);
	s1_len = ft_strlen((char *)s1);
	str_end = (char *)(s1 + s1_len);
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (ft_memchr(set, *s1, set_len) != NULL)
		s1++;
	str_end -= (s1_len != 0);
	while (ft_memchr(set, *str_end, set_len) != NULL)
		str_end--;
	result_len = 0;
	result_len = ft_address_check(str_end, result_len, s1);
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, result_len);
	*(result + result_len) = '\0';
	return (result);
}
