/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:21:27 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/22 13:57:46 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hexavert(char c)
{
	int		i;
	char	*s;

	s = "0123456789abcdef";
	i = 0;
	while (s[i])
	{
		if (s[i] == c || ft_toupper(s[i]) == c)
			return (i);
		i++;
	}
	return (i);
}

void	get_color(t_point *p, char *str)
{
	int		hexa;

	str = ft_strchr(str, ',');
	if (ft_memcmp(str, ",0x", 3))
	{
		p->color = 0xffffff;
		return ;
	}
	str += 3;
	hexa = 0;
	while ((*str >= '0' && *str <= '9') || (*str >= 'a' && *str <= 'f') \
		|| (*str >= 'A' && *str <= 'F'))
	{
		hexa = hexa * 16 + hexavert(*str);
		str++;
	}
	p->color = hexa;
}

t_point	get_point(float x, float y, char *str)
{
	t_point	p;

	p.p[X] = x;
	p.p[Y] = y;
	p.p[Z] = (float)ft_atol(str);
	get_color(&p, str);
	if (p.p[Z] > (float)INT_MAX)
		p.p[Z] = (float)INT_MAX;
	if (p.p[Z] < (float)INT_MIN)
		p.p[Z] = (float)INT_MIN;
	refresh_point(&p);
	return (p);
}

void	get_depth(t_map *map, t_point p)
{
	if (p.p[Z] < map->depth_min)
		map->depth_min = p.p[Z];
	if (p.p[Z] > map->depth_max)
		map->depth_max = p.p[Z];
}
