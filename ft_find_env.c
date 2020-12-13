/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:41:39 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:41:42 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 1. find variable name is inside ENV or not
** and return its value
** 2. to avoid elem is part of varname $PW
** "if (env[i][lens] == '=')"
** 	"return (env[i] + lens + 1);"
*/

char	*ft_find_env(char *elem, char **env)
{
	int	i;
	int	lens;

	i = -1;
	while (env[++i])
	{
		lens = ft_strlen(elem);
		if (!ft_strncmp(env[i], elem, lens))
		{
			if (lens - 1 >= 0 && elem[lens - 1] == '=')
				return (env[i] + lens);
			if (env[i][lens] == '=')
				return (env[i] + lens + 1);
		}
	}
	return (NULL);
}
