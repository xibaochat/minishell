/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:27:38 by xinwang           #+#    #+#             */
/*   Updated: 2019/10/18 04:06:48 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_lens;
	int		i;
	int		j;
	char	*str;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		if (!s1)
			return (ft_strdup(s2));
		return (ft_strdup(s1));
	}
	total_lens = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = ft_strnew(total_lens + 1);
	if (!str)
		return (NULL);
	while ((char)s1[++i])
		str[i] = (char)s1[i];
	while ((char)s2[++j])
		str[i++] = (char)s2[j];
	return (str);
}
