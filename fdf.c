/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:26:18 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/23 17:05:20 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_msg(void)
{
	ft_putendl_fd("Controls ~~~~~", STDOUT_FILENO);
	ft_putendl_fd("Translation\t-> WASD", STDOUT_FILENO);
	ft_putendl_fd("Scale\t\t-> , .", STDOUT_FILENO);
	ft_putendl_fd("Rotation\t-> J-L I-K U-O", STDOUT_FILENO);
	ft_putendl_fd("Change Views\t-> 1 2 3", STDOUT_FILENO);
	ft_putendl_fd("???\t\t-> E", STDOUT_FILENO);
	ft_putendl_fd("Enjoy! ~~~~~", STDOUT_FILENO);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc < 2 || argc > 2)
		ft_error("Usage : ./fdf <filename.fdf>", 0, 0);
	parse_fdf(argv[1], &mlx);
	full_init(&mlx);
	mlx.mlx = mlx_init();
	if (!mlx.mlx)
		ft_error("mlx failure", 1, 1);
	mlx.img = new_img(&mlx);
	mlx.window = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "fdf pls");
	start_render(&mlx);
	print_msg();
	mlx_hook(mlx.window, 02, 1L << 0, key_press, &mlx);
	mlx_hook(mlx.window, 17, 1L << 0, close_window, &mlx);
	mlx_loop_hook(mlx.mlx, e_check, &mlx);
	mlx_loop(mlx.mlx);
}
