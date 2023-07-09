/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:42:21 by hyojocho          #+#    #+#             */
/*   Updated: 2023/03/15 16:42:22 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_sign(const char *str, long long *i)
{
	int	sign;

	sign = 1;
	while ((9 <= str[*i] && str[*i] <= 13) || str[*i] == 32)
		(*i)++;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

long long	ft_atoi_extension(const char *str)
{
	long long	i;
	long long	res;
	int			sign;
	char		c;

	res = 0;
	i = 0;
	sign = ft_sign(str, &i);
	while (str[i])
	{
		c = (char)str[i++];
		if ('0' <= c && c <= '9')
		{
			res *= 10;
			res += (c - '0');
		}
		else
			return (res * sign);
	}
	return (res * sign);
}
