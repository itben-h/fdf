/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:12:38 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 17:04:28 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	transform(t_point **points, t_cam *cam, int len)
{
	int		i;
	t_point	*p;

	p = *points;
	i = -1;
	while (++i < len)
	{
		p[i].r[X] += cam->x;
		p[i].r[Y] += cam->y;
		p[i].r[Z] += cam->z;
	}
}

void	scale(t_point **points, t_cam *cam, int len)
{
	int		i;
	t_point	*p;

	p = *points;
	i = -1;
	while (++i < len)
	{
		p[i].r[X] *= cam->scale;
		p[i].r[Y] *= cam->scale;
		p[i].r[Z] *= cam->scale;
	}
}

void	view_iso(t_mlx *mlx)
{
	mlx->cam->rot[X] = 60;
	mlx->cam->rot[Y] = -40;
	mlx->cam->rot[Z] = 20;
	mlx->cam->fit = 1;
}

void	view_para(t_mlx *mlx)
{
	mlx->cam->rot[X] = 90;
	mlx->cam->rot[Y] = 90;
	mlx->cam->rot[Z] = 0;
	mlx->cam->fit = 1;
}

void	view_flat(t_mlx *mlx)
{
	mlx->cam->rot[X] = 0;
	mlx->cam->rot[Y] = 0;
	mlx->cam->rot[Z] = 0;
	mlx->cam->fit = 1;
}
