/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_inits.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:34:26 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 11:21:26 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	full_init(t_mlx *mlx)
{
	mlx->cam = emalloc(sizeof(t_cam));
	view_iso(mlx);
	mlx->cam->x = WIN_WIDTH / 2;
	mlx->cam->y = WIN_HEIGHT / 2;
	mlx->cam->z = 0;
	mlx->cam->scale = 20;
	mlx->e_mode = 0;
}

float	**init_matrix(void)
{
	float	**matrix;
	int		i;
	int		j;

	matrix = (float **)emalloc(3 * sizeof(float *));
	i = 0;
	while (i < 3)
	{
		matrix[i] = (float *)emalloc(3 * sizeof(float));
		j = 0;
		while (j < 3)
		{
			matrix[i][j] = 0;
			j++;
		}
		i++;
	}
	return (matrix);
}
