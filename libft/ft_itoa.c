/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:22:24 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/05 10:03:36 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_make_n_size(int n)
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

static void	ft_put_n_to_result(char *result, int n, int n_size)
{
	result[n_size] = '\0';
	n_size--;
	while (n > 0)
	{
		result[n_size] = (n % 10) + '0';
		n_size--;
		n /= 10;
	}
	if (n_size == 0)
		result[n_size] = '-';
}

char	*ft_itoa(int n)
{
	int		n_size;
	int		minus_flag;
	char	*result;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	minus_flag = 0;
	if (n < 0)
	{
		minus_flag = 1;
		n *= -1;
	}
	n_size = ft_make_n_size(n);
	if (minus_flag)
		n_size++;
	result = (char *)malloc(sizeof(char) * (n_size + 1));
	if (result == NULL)
		return (NULL);
	ft_put_n_to_result(result, n, n_size);
	return (result);
}
