/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_Linux_mouse_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:36:53 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/26 12:37:00 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	os_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	mlx_mouse_move(mlx_ptr, win_ptr, x, y);
}

void	os_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	mlx_mouse_get_pos(mlx_ptr, win_ptr, x, y);
}
