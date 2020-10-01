/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:29:57 by xinwang           #+#    #+#             */
/*   Updated: 2020/04/16 10:05:05 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*empty_string(void)
{
	char	*p;

	p = (char *)malloc(sizeof(char));
	if (!p)
		return (NULL);
	p[0] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	char			*sub_str;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *)s;
	if (start >= (unsigned int)ft_strlen(str))
		return (empty_string());
	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (!s || !sub_str)
		return (NULL);
	while (i < len && str[start])
		sub_str[i++] = str[start++];
	sub_str[i] = '\0';
	return (sub_str);
}
