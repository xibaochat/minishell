/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:29:06 by xinwang           #+#    #+#             */
/*   Updated: 2020/04/16 09:53:47 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	char	*s;

	i = 0;
	s = (char *)str;
	if (to_find[i] == '\0')
		return (s);
	while (s[i] && i < len)
	{
		tmp = i;
		j = 0;
		while (s[tmp] && to_find[j]
			   && (s[tmp] == to_find[j]) && tmp < len)
		{
			tmp++;
			j++;
			if (!to_find[j])
				return (s + i);
		}
		i++;
	}
	return (NULL);
}
