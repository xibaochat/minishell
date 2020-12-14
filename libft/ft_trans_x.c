/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trans_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:25:59 by xinwang           #+#    #+#             */
/*   Updated: 2020/12/13 17:38:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(uintmax_t n)
{
	int				size;

	size = 1;
	while (n > 16)
	{
		size++;
		n = n / 16;
	}
	return (size);
}

static char	*get_converted_str(char *str, uintmax_t res, int *i)
{
	static char	base[17] = "0123456789abcdef";

	if (res >= 16)
		get_converted_str(str, res / 16, i);
	str[(*i)++] = base[res % 16];
	return (str);
}

char		*ft_trans_to_x(uintmax_t n)
{
	int				i;
	uintmax_t		res;
	char			*str;

	i = 0;
	res = n;
	str = (char *)malloc(get_size(n) + 1);
	if (!str)
		return (NULL);
	str = get_converted_str(str, res, &i);
	str[i] = '\0';
	return (str);
}
