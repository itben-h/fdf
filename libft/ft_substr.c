/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhowe <bhowe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:26:50 by bhowe             #+#    #+#             */
/*   Updated: 2024/07/05 12:01:09 by bhowe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	len_s;
	size_t	len_new;

	len_new = 0;
	len_s = ft_strlen(s);
	if (start > len_s)
		start = len_s;
	while (s[start] && start < len_s && len_new < len)
	{
		start++;
		len_new++;
	}
	start -= len_new;
	new = (char *)malloc((len_new + 1) * sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, s + start, len_new);
	new[len_new] = '\0';
	return (new);
}
