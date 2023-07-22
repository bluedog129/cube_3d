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
# include <math.h>
# include <stdio.h>//

# include "libft.h"
# include "structures.h"
# include "mlx.h"
# include "os_define.h"

# define WIDTH 640
# define HEIGHT 480

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

enum e_door_state
{
	CLOSE = 0,
	OPENING = 1,
	OPEN = 2,
	CLOSING = 3
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
int			is_blank(char c);

// free_utils
void		free_2d_arr(char **arr);
void		finish_cub(t_map *map_info, t_parse_info *parse_info);
void		exit_error(char *str, t_map *map_info, t_parse_info *parse_info);

// linked list
void		ft_lstadd_back(t_map_node *lst, t_map_node *new);
t_map_node	*ft_lstlast(t_map_node *lst);
void		free_lst_node(t_map_node *head);

// engine part

void		engine_main(t_map *map_info, t_parse_info *parse_info);

int			create_trgb(int t, int r, int g, int b);
int			pixel_from_image(t_img_data *img, int x, int y);
void		pixel_put_to_image(t_img_data *img, int x, int y, int color);

int			my_key_pressed_hook(int keycode, t_game_data *game_data);
int			my_key_released_hook(int keycode, t_game_data *game_data);
int			my_mouse_motion_hook(int x, int y, t_game_data *game_data);
int			my_loop_hook(t_game_data *game_data);

void		rotate_vector2(t_vec2d *vec2, float degree);

void		move_event(t_game_data *game_data);

void		draw_screen(t_game_data *game_data);
void		drawing_walls(t_game_data *game_data, t_img_data *screen);
// void		drawing_vdoors(t_game_data *game_data, t_img_data *screen);
// void		drawing_hdoors(t_game_data *game_data, t_img_data *screen);
void		drawing_doors(t_game_data *game_data, t_img_data *screen);
void		drawing_vdoors(t_game_data *game_data, t_img_data *screen, int screen_x);
void		drawing_hdoors(t_game_data *game_data, t_img_data *screen, int screen_x);
void		drawing_minimap(t_game_data *game_data);

void		os_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y);
void		os_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y);

void		camera_setup1(t_game_data *game_data);
int			load_textures1(t_game_data	*game_data);
int			load_textures2(t_game_data	*game_data);

t_list		*get_door(t_list *door_list, int x, int y);
void		door_update(void *content);
t_list		*new_door(int x, int y);
int			get_door_list(t_map *map_info, t_list **door_list);
void		interact_doors(t_game_data *game_data);

void		raycaster_setup(t_raycaster *rc, t_camera cam, int screen_x);
void		dda_algorythm2(char **map, t_raycaster *rc, t_camera *cam);
void		dda_algorythm3(char **map, t_raycaster *rc, t_camera *cam);
void		draw_textes(t_game_data *game_data);
int			is_passable(t_game_data *game_data, int x, int y);
void		draw_vertical_line(t_img_data *target_texture, t_img_data *img, \
int x, t_draw_info *draw_info);

void		exit_cub3d(t_game_data *game_data);

#endif