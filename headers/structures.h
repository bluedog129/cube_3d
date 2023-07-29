/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 14:16:34 by hyojocho          #+#    #+#             */
/*   Updated: 2023/07/29 18:28:04 by yonghyle         ###   ########.fr       */
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
	char				**map_board;
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
}	t_parse_info;

// -------------------

typedef struct s_vec2d
{
	float	x;
	float	y;
}	t_vec2d;

typedef struct s_raycaster
{
	float	camera_x;
	t_vec2d	dir;
	t_vec2d	map_check;
	t_vec2d	side_dist;
	t_vec2d	delta_dist;
	float	perp_wall_dist;
	t_vec2d	step;
	int		side;
}	t_raycaster;

typedef struct s_camera
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
	float	move_speed;
	float	rotate_speed;
}	t_camera;

typedef struct s_img_data
{
	void	*img_ptr;
	char	*img_addr;
	int		img_bpp;
	int		img_line_len;
	int		img_endian;
	int		img_width;
	int		img_height;
}	t_img_data;

typedef struct s_draw_info
{
	int			line_len;
	int			draw_start;
	int			draw_end;
	float		wall_x;
	int			texture_idx;
	t_img_data	*target_texture;
	t_vec2d		texture_pos;
	int			color;
}	t_draw_info;

typedef struct s_game_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			*map_info;
	t_parse_info	*parse_info;
	t_img_data		wall_texture[4];
	t_vec2d			move_input;
	t_vec2d			rot_input;
	t_camera		camera;

}	t_game_data;

#endif