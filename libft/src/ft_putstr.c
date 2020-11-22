/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osshit <osshit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/18 19:39:18 by osshit            #+#    #+#             */
/*   Updated: 2020/03/18 19:39:43 by osshit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_echo(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (s[i] != 3)
				write(1, &s[i], 1);
			i++;
		}
	}
}

void	ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}
