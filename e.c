/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:04:06 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 16:55:38 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	e_color(void)
{
	return (rand() % (0xffffff + 1));
}

static void	e_do(int r, t_point *p)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (r == 1 || r == 5 || r == 8)
		x = 1;
	if (r == 2 || r == 6 || r == 7)
		x = -1;
	if (r == 3 || r == 7 || r == 8)
		y = 1;
	if (r == 4 || r == 5 || r == 6)
		y = -1;
	p->r[X] += x;
	p->r[Y] += y;
}

void	e_mode(t_mlx *mlx)
{
	t_point	*p;
	int		r;
	int		i;

	p = mlx->map->points;
	i = -1;
	while (++i < mlx->map->len)
	{
		r = rand() % 9;
		e_do(r, &p[i]);
	}
}

int	e_check(t_mlx *mlx)
{
	if (mlx->e_mode)
	{
		start_render(mlx);
	}
	return (0);
}
