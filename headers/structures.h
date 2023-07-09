/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: choihyojong <choihyojong@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:16:34 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/09 18:17:29 by choihyojong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}			t_map_node;

typedef struct s_map
{
	int					width;
	int					height;
	struct s_map_node	*head_node;
	struct s_side_info	*side_info;
}				t_map;

typedef struct s_side_info
{
	char	*north_tex;
	char	*south_tex;
	char	*west_tex;
	char	*east_tex;
	int		floor_rgb;
	int		ceiling_rgb;
}				t_side_info;

typedef struct s_parse_info
{
	int		fd;
	int		north_tex_count;
	int		south_tex_count;
	int		west_tex_count;
	int		east_tex_count;
	int		floor_rgb_count;
	int		ceiling_rgb_count;
	int		start_position_count;
	int		line_type;
	char	*line;
	char	**map_board;
}	t_parse_info;

#endif