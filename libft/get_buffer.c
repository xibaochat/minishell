/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buffer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:38:59 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 17:39:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**get_buffer(void)
{
	static char	*buffer = NULL;

	return (&buffer);
}

void	ft_print_buffer(void)
{
	char	**buf;

	buf = get_buffer();
	ft_printf("%s\n", *buf);
}
