/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:43:58 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/22 17:00:51 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	*emalloc(size_t size)
{
	void	*res;

	res = (void *)malloc(size);
	if (!res)
		ft_error("malloc fail", 1, 1);
	return (res);
}

void	free_cmap(char ***map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		ft_free_arr(map[i]);
		i++;
	}
	free(map);
}

void	free_matrix(float **matrix)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	close_window(t_mlx *mlx)
{
	if (mlx->window)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		ft_putendl_fd("Window Closed!", STDOUT_FILENO);
		ft_cleanup(mlx);
	}
	exit(EXIT_SUCCESS);
}

void	ft_cleanup(t_mlx *mlx)
{
	del_img(mlx, mlx->img);
	free(mlx->cam);
	free(mlx->map->points);
	free(mlx->map);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
}
