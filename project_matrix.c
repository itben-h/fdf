/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 23:10:34 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 11:12:50 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mul_mat(float **matrix, t_point *p)
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			p->w[i] += matrix[i][j] * p->r[j];
			j++;
		}
		i++;
	}
	p->r[X] = p->w[X];
	p->r[Y] = p->w[Y];
	p->r[Z] = p->w[Z];
	p->w[X] = 0;
	p->w[Y] = 0;
	p->w[Z] = 0;
}

void	rotate_x(t_point **points, float deg, int len)
{
	int		i;
	float	rad;
	float	**matrix;
	t_point	*p;

	p = *points;
	rad = deg * PI / 180;
	matrix = init_matrix();
	matrix[0][0] = 1;
	matrix[1][1] = cos(rad);
	matrix[1][2] = -sin(rad);
	matrix[2][1] = sin(rad);
	matrix[2][2] = cos(rad);
	i = -1;
	while (++i < len)
		mul_mat(matrix, &p[i]);
	free_matrix(matrix);
}

void	rotate_y(t_point **points, float deg, int len)
{
	int		i;
	float	rad;
	float	**matrix;
	t_point	*p;

	p = *points;
	rad = deg * PI / 180;
	matrix = init_matrix();
	matrix[0][0] = cos(rad);
	matrix[0][2] = sin(rad);
	matrix[1][1] = 1;
	matrix[2][0] = -sin(rad);
	matrix[2][2] = cos(rad);
	i = -1;
	while (++i < len)
		mul_mat(matrix, &p[i]);
	free_matrix(matrix);
}

void	rotate_z(t_point **points, float deg, int len)
{
	int		i;
	float	rad;
	float	**matrix;
	t_point	*p;

	p = *points;
	rad = deg * PI / 180;
	matrix = init_matrix();
	matrix[0][0] = cos(rad);
	matrix[0][1] = -sin(rad);
	matrix[1][0] = sin(rad);
	matrix[1][1] = cos(rad);
	matrix[2][2] = 1;
	i = -1;
	while (++i < len)
		mul_mat(matrix, &p[i]);
	free_matrix(matrix);
}

void	orto(t_point **points, int len)
{
	int		i;
	float	**matrix;
	t_point	*p;

	p = *points;
	matrix = init_matrix();
	matrix[0][0] = 1;
	matrix[1][1] = 1;
	i = -1;
	while (++i < len)
		mul_mat(matrix, &p[i]);
	free_matrix(matrix);
}
