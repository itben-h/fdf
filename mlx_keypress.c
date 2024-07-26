/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keypress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:37:56 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 17:04:11 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_rotate(int keycode, t_mlx *mlx)
{
	if (keycode == XK_i)
		mlx->cam->rot[X] += 10;
	if (keycode == XK_k)
		mlx->cam->rot[X] -= 10;
	if (keycode == XK_l)
		mlx->cam->rot[Y] += 10;
	if (keycode == XK_j)
		mlx->cam->rot[Y] -= 10;
	if (keycode == XK_o)
		mlx->cam->rot[Z] += 10;
	if (keycode == XK_u)
		mlx->cam->rot[Z] -= 10;
	return (0);
}

static int	key_translate(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Right)
		mlx->cam->x += 5;
	if (keycode == XK_Left)
		mlx->cam->x -= 5;
	if (keycode == XK_Down)
		mlx->cam->y += 5;
	if (keycode == XK_Up)
		mlx->cam->y -= 5;
	return (0);
}

static int	key_zoom(int keycode, t_mlx *mlx)
{
	if (keycode == XK_period)
		mlx->cam->scale += 0.2;
	if (keycode == XK_comma)
		mlx->cam->scale -= 0.2;
	return (0);
}

static int	e_toggle(t_mlx *mlx)
{
	if (!mlx->e_mode)
		mlx->e_mode = 1;
	else
		mlx->e_mode = 0;
	return (0);
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == XK_Escape)
		close_window(mlx);
	if (keycode == XK_period || keycode == XK_comma)
		key_zoom(keycode, mlx);
	if (keycode == XK_Up || keycode == XK_Down
		|| keycode == XK_Right || keycode == XK_Left)
		key_translate(keycode, mlx);
	if (keycode == XK_j || keycode == XK_l
		|| keycode == XK_i || keycode == XK_k
		|| keycode == XK_u || keycode == XK_o)
		key_rotate(keycode, mlx);
	if (keycode == XK_1)
		view_iso(mlx);
	if (keycode == XK_2)
		view_para(mlx);
	if (keycode == XK_3)
		view_flat(mlx);
	if (keycode == XK_f)
		refit(mlx);
	if (keycode == XK_e)
		e_toggle(mlx);
	start_render(mlx);
	return (0);
}
