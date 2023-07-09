/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_lower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:26:41 by hyojocho          #+#    #+#             */
/*   Updated: 2023/01/30 18:49:13 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_make_n_size(unsigned int n)
{
	int	count;

	count = 0;
	while (n)
	{
		count++;
		n /= 16;
	}
	return (count);
}

static void	ft_put_n_to_result(char *result, unsigned int n, int n_size)
{
	result[n_size] = '\0';
	n_size--;
	while (n > 0)
	{
		result[n_size] = "0123456789abcdef"[n % 16];
		n_size--;
		n /= 16;
	}
	if (n_size == 0)
		result[n_size] = '-';
}

char	*ft_uitoa_lower(unsigned int n)
{
	int		n_size;
	char	*result;

	if (n == 0)
		return (ft_strdup("0"));
	n_size = ft_make_n_size(n);
	result = (char *)malloc(sizeof(char) * (n_size + 1));
	if (result == NULL)
		return (NULL);
	ft_put_n_to_result(result, n, n_size);
	return (result);
}
