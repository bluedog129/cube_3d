/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:06:39 by hyojocho          #+#    #+#             */
/*   Updated: 2022/12/01 10:49:21 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = (long long)n;
	if (num < 0)
	{
		num *= -1;
		ft_putchar_fd(45, fd);
	}
	if (num > 9)
		ft_putnbr_fd((num / 10), fd);
	ft_putchar_fd((num % 10 + '0'), fd);
}
