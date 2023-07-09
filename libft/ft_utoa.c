/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:01:32 by hyojocho          #+#    #+#             */
/*   Updated: 2023/01/28 16:20:07 by hyojocho         ###   ########.fr       */
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
		n /= 10;
	}
	return (count);
}

static void	ft_put_n_to_result(char *result, unsigned int n, int n_size)
{
	result[n_size] = '\0';
	n_size--;
	while (n > 0)
	{
		result[n_size] = (n % 10) + '0';
		n_size--;
		n /= 10;
	}
}

char	*ft_utoa(unsigned int n)
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
