/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:53:54 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/22 18:47:25 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_blank(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	open_file(char *cub_file)
{
	int	fd;

	fd = open(cub_file, O_RDONLY);
	if (fd == -1)
		return (ERROR);
	return (fd);
}

int	check_line_empty(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

void	print_error(char *str)
{
	printf("%s", str);
	exit(ERROR);
}
