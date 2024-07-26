/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:30:47 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 16:45:28 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line_slopemore(t_img *img, t_line line)
{
	int	i;
	int	col;

	i = -1;
	line.p = 2 * abs(line.dx) - abs(line.dy);
	while (++i < abs(line.dy))
	{
		if (line.dy > 0)
			line.sy++;
		else
			line.sy--;
		if (line.p < 0)
			line.p += 2 * abs(line.dx);
		else
		{
			if (line.dx > 0)
				line.sx++;
			else
				line.sx--;
			line.p += 2 * abs(line.dx) - 2 * abs(line.dy);
		}
		col = lerp_col(line, 1, line.p1->color, line.p2->color);
		set_img_pixel(img, line.sx, line.sy, col);
	}
}

static void	draw_line_slopeless(t_img *img, t_line line)
{
	int	i;
	int	col;

	i = -1;
	line.p = 2 * abs(line.dy) - abs(line.dx);
	while (++i < abs(line.dx))
	{
		if (line.dx > 0)
			line.sx++;
		else
			line.sx--;
		if (line.p < 0)
			line.p += 2 * abs(line.dy);
		else
		{
			if (line.dy > 0)
				line.sy++;
			else
				line.sy--;
			line.p += 2 * abs(line.dy) - 2 * abs(line.dx);
		}
		col = lerp_col(line, 0, line.p1->color, line.p2->color);
		set_img_pixel(img, line.sx, line.sy, col);
	}
}

static void	start_line(t_mlx *mlx, t_point *p1, t_point *p2)
{
	t_line	line;

	if (!(oob_check(p1->r[X], p1->r[Y]) && oob_check(p2->r[X], p2->r[Y])))
	{
		line.p1 = p1;
		line.p2 = p2;
		line.sx = p1->r[X];
		line.sy = p1->r[Y];
		line.dx = p2->r[X] - p1->r[X];
		line.dy = p2->r[Y] - p1->r[Y];
		line.e_mode = mlx->e_mode;
		if (abs(line.dx) > abs(line.dy))
			draw_line_slopeless(mlx->img, line);
		else
			draw_line_slopemore(mlx->img, line);
	}
}

static void	render_map(t_mlx *mlx)
{
	t_point	*p;
	int		i;
	int		j;

	i = -1;
	while (++i < mlx->map->height)
	{
		j = -1;
		while (++j < mlx->map->width)
		{
			p = pin_point(mlx, i, j);
			if (j + 1 < mlx->map->width)
				start_line(mlx, p, pin_point(mlx, i, j + 1));
			if (i + 1 < mlx->map->height)
				start_line(mlx, p, pin_point(mlx, i + 1, j));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img->img, 0, 0);
}

void	start_render(t_mlx *mlx)
{
	clear_img(mlx->img);
	reorient(mlx);
	if (mlx->cam->fit)
		refit(mlx);
	else
		render_map(mlx);
}
