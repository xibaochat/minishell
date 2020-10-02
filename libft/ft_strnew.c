/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maobe <maobe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 01:29:39 by maobe             #+#    #+#             */
/*   Updated: 2020/10/02 01:29:56 by maobe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(int size)
{
	char *ptr;
	int  i;

	if (!(ptr = (char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		ptr[i++] = 0;
	return (ptr);
}
