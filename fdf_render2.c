/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_render2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:30:03 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 16:56:07 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	fraction(float p1, float p2, int p)
{
	if (p1 == p2)
		return (0);
	return ((p - p1) / (p2 - p1));
}

static float	lerp(int a, int b, float frac)
{
	if (a == b)
		return (a);
	return (a + (b - a) * frac);
}

int	lerp_col(t_line line, int d, int p1_col, int p2_col)
{
	int		r;
	int		g;
	int		b;
	float	frac;

	if (line.e_mode)
		return (e_color());
	if (line.p1->color == line.p2->color)
		return (line.p1->color);
	if (!d)
		frac = fraction(line.p1->r[X], line.p2->r[X], line.sx);
	else
		frac = fraction(line.p1->r[Y], line.p2->r[Y], line.sy);
	p1_col = line.p1->color;
	p2_col = line.p2->color;
	r = lerp((p1_col >> 16) & 0xff, (p2_col >> 16) & 0xff, frac);
	g = lerp((p1_col >> 8) & 0xff, (p2_col >> 8) & 0xff, frac);
	b = lerp(p1_col & 0xff, p2_col & 0xff, frac);
	return (r << 16 | g << 8 | b);
}

void	reorient(t_mlx *mlx)
{
	int		i;
	t_point	*p;

	if (mlx->map->points->p != mlx->map->points->r)
	{
		p = mlx->map->points;
		i = -1;
		while (++i < mlx->map->len)
			refresh_point(&p[i]);
	}
	rotate_x(&mlx->map->points, mlx->cam->rot[X], mlx->map->len);
	rotate_y(&mlx->map->points, mlx->cam->rot[Y], mlx->map->len);
	rotate_z(&mlx->map->points, mlx->cam->rot[Z], mlx->map->len);
	orto(&mlx->map->points, mlx->map->len);
	scale(&mlx->map->points, mlx->cam, mlx->map->len);
	transform(&mlx->map->points, mlx->cam, mlx->map->len);
	if (mlx->e_mode)
		e_mode(mlx);
}

void	refit(t_mlx *mlx)
{
	t_point	p;
	int		i;
	int		res;

	i = -1;
	res = 0;
	while (++i < mlx->map->len)
	{
		p = mlx->map->points[i];
		if (oob_check(p.r[X], p.r[Y]))
		{
			mlx->cam->scale -= 0.2;
			res = 1;
			break ;
		}
	}
	mlx->cam->fit = res;
	start_render(mlx);
}
