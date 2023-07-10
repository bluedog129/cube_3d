/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 13:56:19 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/10 22:40:27 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "structures.h"
# include "../libft/libft.h"

enum e_cub3d_enum
{
	SUCCESS = 1,
	ERROR = -1,
	FALSE = 0,
	TRUE = 1
};

enum e_side_type_enum
{
	NO = 1,
	SO = 2,
	WE = 3,
	EA = 4,
	S = 5,
	F = 6,
	C = 7,
};

enum e_check_type_enum
{
	MAP = 8,
	EMPTY_LINE = 9,
	SIDE_TEXTURE = 11,
	RGB = 12
};

// parsing
void		parse_cub_file(char *cub_file, t_map *map_info, \
										t_parse_info *parse_info);

// args_validation
void		validate_args(int argc, char *cub_file);

// initailize
void		initialize(char *cub_file, t_map *map_info, \
									t_parse_info *parse_info);

// side_info_get
int			get_texture_path(char **texture_info, t_map *map_info, \
						t_parse_info *parse_info);
int			get_rgb(char *rgb_val, t_map *map_info, t_parse_info *parse_info);

// line_validation
int			check_type(char *line);
void		validate_texture(char *tex_line, t_map *map_info, \
											t_parse_info *parse_info);
void		validate_rgb(char *tex_line, t_map *map_info, \
											t_parse_info *parse_info);
void		validate_map(char *map_line, t_map *map_info, \
										t_parse_info *parse_info);
int			validate_all_lines(t_parse_info *parse_info);

// map_validation
void		valid_map_characters(char *line, t_map *map_info, \
											t_parse_info *parse_info);
int			validate_edge_part(t_parse_info *parse_info, t_map *map_info, \
						int height, int width);

// making_map_array
void		make_array_map(t_map *map_info, t_parse_info *parse_info);

// line_parse_utils
void		print_error(char *str);
int			check_line_empty(char *line);
int			open_file(char *cub_file);

// free_utils
void		free_2d_arr(char **arr);
void		finish_cub(t_map *map_info, t_parse_info *parse_info);
void		exit_error(char *str, t_map *map_info, t_parse_info *parse_info);

// linked list
void		ft_lstadd_back(t_map_node *lst, t_map_node *new);
t_map_node	*ft_lstlast(t_map_node *lst);
void		free_lst_node(t_map_node *head);

#endif