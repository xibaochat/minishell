/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:29:16 by xinwang           #+#    #+#             */
/*   Updated: 2019/10/18 04:32:30 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	int		i;
	int		j;
	int		mark;

	i = 0;
	j = 0;
	mark = 0;
	s = (char *)str;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			j = i;
			mark = 1;
		}
		i++;
	}
	if (mark)
		return (s + j);
	if (!c)
		return (s + i);
	return (NULL);
}
