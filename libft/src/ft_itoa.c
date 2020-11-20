/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:49:03 by xinwang           #+#    #+#             */
/*   Updated: 2020/04/16 10:05:25 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_converted_str(char *str, unsigned int res, int *i)
{
	if (res >= 10)
		get_converted_str(str, res / 10, i);
	str[(*i)++] = res % 10 + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	res;
	char			*str;

	i = 0;
	res = n;
	str = (char *)malloc(get_nb_size(n) + 1);
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[i++] = '-';
		res = -1 * n;
	}
	str = get_converted_str(str, res, &i);
	str[i] = '\0';
	return (str);
}
