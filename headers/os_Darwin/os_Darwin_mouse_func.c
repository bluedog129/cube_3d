/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   os_Darwin_mouse_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:38:34 by yonghyle          #+#    #+#             */
/*   Updated: 2023/07/26 12:38:41 by yonghyle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	os_mouse_move(void *mlx_ptr, void *win_ptr, int x, int y)
{
	(void)mlx_ptr;
	mlx_mouse_move(win_ptr, x, y);
}

void	os_mouse_get_pos(void *mlx_ptr, void *win_ptr, int *x, int *y)
{
	(void)mlx_ptr;
	mlx_mouse_get_pos(win_ptr, x, y);
}
