/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew_with_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maobe <maobe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 22:04:04 by maobe             #+#    #+#             */
/*   Updated: 2020/10/09 22:04:06 by maobe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew_with_char(int size, char c)
{
	char	*ptr;
	int		i;

	if (!(ptr = (char *)malloc(size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
		ptr[i++] = c;
	ptr[i] = '\0';
	return (ptr);
}
