/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:17:12 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 14:50:07 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_img_pixel(t_img *img, int x, int y, int color)
{
	if (oob_check(x, y))
		return ;
	*(unsigned int *)(img->ptr + (y * img->line_length \
		+ x * img->bits_per_pixel)) = color;
}

void	clear_img(t_img *img)
{
	ft_bzero(img->ptr, WIN_WIDTH * WIN_HEIGHT * img->bits_per_pixel);
}

t_img	*del_img(t_mlx *mlx, t_img *img)
{
	if (img)
	{
		if (img->img)
			mlx_destroy_image(mlx->mlx, img->img);
		free(img);
		img = NULL;
	}
	return (0);
}

t_img	*new_img(t_mlx *mlx)
{
	t_img	*img;

	img = (t_img *)malloc(sizeof(t_img));
	if (!img)
		return (0);
	img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img->img)
		return (del_img(mlx, img));
	img->ptr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	img->bits_per_pixel /= 8;
	return (img);
}
