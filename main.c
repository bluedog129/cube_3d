/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:05:00 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/09 22:46:38 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

int main(int argc, char **argv)
{
	t_map			map_info;
	t_parse_info	parse_info;
	
	validate_args(argc, argv[1]);
	parse_cub_file(argv[1], &map_info, &parse_info);
	make_array_map(&map_info, &parse_info);
	int i = 0;
	while (i < map_info.height)
	{
		printf("%s\n", parse_info.map_board[i]);
		i++;
	}
}
