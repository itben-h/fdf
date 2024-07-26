/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 14:44:57 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/24 13:33:03 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_lines(char *arg)
{
	int		res;
	int		fdf;
	char	*line;

	res = 0;
	fdf = open(arg, O_RDONLY);
	if (fdf == -1)
		ft_error("Bad .fdf file", 1, 1);
	while (1)
	{
		line = get_next_line(fdf);
		if (!line)
			break ;
		free(line);
		res++;
	}
	close(fdf);
	if (res == 0)
		ft_error("Too few map points. Exiting..", 0, 0);
	return (res);
}

static char	***store_map(char *arg, t_map *map)
{
	int		i;
	int		fdf;
	char	*line;
	char	***c_map;

	fdf = open(arg, O_RDONLY);
	if (fdf == -1)
		ft_error("Bad .fdf file", 1, 1);
	i = -1;
	c_map = (char ***)emalloc((map->height + 1) * sizeof(char **));
	while (++i < map->height)
	{
		line = get_next_line(fdf);
		c_map[i] = ft_split(line, ' ');
		free(line);
	}
	c_map[i] = 0;
	return (c_map);
}

static int	check_width(char ***c_map, t_map *map)
{
	int	i;
	int	line_len;
	int	a;
	int	b;

	line_len = arrlen(c_map[0]);
	i = -1;
	while (++i < map->height)
	{
		a = (line_len != arrlen(c_map[i]));
		b = (line_len == 1 && map->height == 1);
		if (a || b)
		{
			free_cmap(c_map);
			free(map);
			if (a)
				ft_error("Unequal line lengths. Exiting..", 0, 0);
			else
				ft_error("Too few map points. Exiting..", 0, 0);
		}
	}
	return (line_len);
}

static t_point	*init_map(char ***c_map, t_map *map)
{
	t_point	*p;
	int		i;
	int		j;
	float	i_c;
	float	j_c;

	map->depth_min = INT_MAX;
	map->depth_max = INT_MIN;
	map->len = map->width * map->height;
	p = (t_point *)emalloc(map->len * sizeof(t_point));
	i = -1;
	i_c = -(map->height - 1) / 2;
	while (c_map[++i])
	{
		j = -1;
		j_c = (map->width - 1) / 2;
		while (c_map[i][++j])
		{
			p[i * map->width + j] = get_point(i_c, j_c, c_map[i][j]);
			get_depth(map, p[i * map->width + j]);
			j_c -= 1;
		}
		i_c += 1;
	}
	return (p);
}

void	parse_fdf(char *arg, t_mlx *mlx)
{
	int		len;
	int		height;
	char	***c_map;

	len = ft_strlen(arg);
	if (ft_strncmp(arg + (len - 4), ".fdf", 4))
		ft_error("File is not fdf. Exiting...", 0, 0);
	height = count_lines(arg);
	mlx->map = emalloc(sizeof(t_map));
	mlx->map->height = height;
	c_map = store_map(arg, mlx->map);
	mlx->map->width = check_width(c_map, mlx->map);
	mlx->map->points = init_map(c_map, mlx->map);
	free_cmap(c_map);
}
