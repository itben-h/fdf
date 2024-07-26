/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:35:57 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 16:22:48 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *msg, int err, int exit_no)
{
	if (err)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
	if (exit_no)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int	arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

t_point	*pin_point(t_mlx *mlx, int i, int j)
{
	return (&mlx->map->points[i * mlx->map->width + j]);
}

void	refresh_point(t_point *p)
{
	p->r[X] = p->p[X];
	p->r[Y] = p->p[Y];
	p->r[Z] = p->p[Z];
	p->w[X] = 0;
	p->w[Y] = 0;
	p->w[Z] = 0;
}

int	oob_check(int x, int y)
{
	return (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT);
}
