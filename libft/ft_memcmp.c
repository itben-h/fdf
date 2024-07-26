/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:03:36 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/17 14:07:55 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (-1);
	while (*s1_ptr == *s2_ptr && n - 1 > 0)
	{
		s1_ptr++;
		s2_ptr++;
		n--;
	}
	return (*s1_ptr - *s2_ptr);
}
