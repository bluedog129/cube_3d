/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojocho <hyojocho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:42:18 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/18 15:56:01 by hyojocho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_cube_file(char *cub_file)
{
	char	*start;
	char	*slash;
	char	*str;

	start = NULL;
	str = ".cub";
	start = ft_strnstr(cub_file, str, ft_strlen(cub_file));
	if (start == NULL)
		print_error("Error: Invalid file name\n");
	if (start[4] != '\0')
		print_error("Error: Invalid file name\n");
	slash = ft_strrchr(cub_file, '/');
	if (slash == NULL)
		return ;
	while (++slash != start)
	{
		if (*slash == '.')
			print_error("Error: Invalid file name\n");
	}
}

void	validate_args(int argc, char *cubfile)
{
	if (argc != 2)
		print_error("Error: Invalid number of arguments\n");
	validate_cube_file(cubfile);
}
