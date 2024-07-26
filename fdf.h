/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:49:45 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/26 14:04:15 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <X11/keysym.h>
# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"

# define PI			3.14159265358979323846
# define X			0
# define Y			1
# define Z			2
# define WIN_WIDTH	960
# define WIN_HEIGHT	540

typedef struct s_cam
{
	float	x;
	float	y;
	float	z;
	float	rot[3];
	float	scale;
	int		fit;
}	t_cam;

typedef struct s_point
{
	float	p[3];
	float	w[3];
	float	r[3];
	int		color;
	int		color_d;
}	t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		len;
	int		depth_min;
	int		depth_max;
	t_point	*points;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	t_img	*img;
	t_map	*map;
	t_cam	*cam;
	int		e_mode;
}	t_mlx;

typedef struct s_line
{
	t_point	*p1;
	t_point	*p2;
	int		sx;
	int		sy;
	int		dx;
	int		dy;
	int		p;
	int		e_mode;
}	t_line;

void	full_init(t_mlx *mlx);
float	**init_matrix(void);
void	parse_fdf(char *arg, t_mlx *mlx);
void	ft_error(char *msg, int err, int exit_no);
void	*emalloc(size_t size);
void	free_cmap(char ***map);
void	free_matrix(float **matrix);
int		arrlen(char **arr);
void	ft_cleanup(t_mlx *mlx);
t_point	get_point(float x, float y, char *str);
void	get_depth(t_map *map, t_point p);
t_point	*pin_point(t_mlx *mlx, int i, int j);
void	refresh_point(t_point *p);
int		start_render(t_mlx *mlx);
t_img	*new_img(t_mlx *mlx);
t_img	*del_img(t_mlx *mlx, t_img *img);
void	clear_img(t_img *img);
void	set_img_pixel(t_img *img, int x, int y, int color);
void	view_iso(t_mlx *mlx);
void	view_para(t_mlx *mlx);
void	view_flat(t_mlx *mlx);
void	rotate_x(t_point **points, float deg, int len);
void	rotate_y(t_point **points, float deg, int len);
void	rotate_z(t_point **points, float deg, int len);
void	orto(t_point **points, int len);
void	transform(t_point **points, t_cam *cam, int len);
void	scale(t_point **points, t_cam *cam, int len);
int		lerp_col(t_line line, int d, int p1_col, int p2_col);
void	reorient(t_mlx *mlx);
void	refit(t_mlx *mlx);
int		oob_check(int x, int y);
int		key_press(int keycode, t_mlx *mlx);
int		close_window(t_mlx *mlx);
void	e_mode(t_mlx *mlx);
int		e_color(void);

#endif
