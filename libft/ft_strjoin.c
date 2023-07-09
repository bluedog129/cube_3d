/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:47:53 by hyojocho          #+#    #+#             */
/*   Updated: 2022/11/27 20:47:55 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;
	int		result_len;

	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	result_len = s1_len + s2_len + 1;
	result = (char *)malloc(sizeof(char) * (result_len));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, result_len);
	ft_strlcat(result, s2, result_len);
	return (result);
}
