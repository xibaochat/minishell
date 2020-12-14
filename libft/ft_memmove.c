/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:57:41 by xinwang           #+#    #+#             */
/*   Updated: 2019/10/18 12:37:39 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	s = (char *)src;
	d = (char *)dest;
	if (s < d)
	{
		while (++i <= n)
			d[n - i] = s[n - i];
	}
	else
		ft_memcpy(d, s, n);
	return (dest);
}
