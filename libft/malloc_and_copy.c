/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_and_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:39 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 17:41:47 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_malloc_and_copy(char *src)
{
	int		lens;
	char	*str;

	if (src)
	{
		lens = ft_strlen(src);
		str = ft_strnew(lens + 1);
		ft_strncat(str, src, lens);
		return (str);
	}
	return (NULL);
}
