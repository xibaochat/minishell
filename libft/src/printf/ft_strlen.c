/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:28:29 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/29 17:43:53 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t		ft_strlen(const char *str)
{
	size_t	i;
	size_t	lens;

	i = -1;
	lens = 0;
	if (!str)
		return (0);
	while (str[++i])
		lens++;
	return (lens);
}
