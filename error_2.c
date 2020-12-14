/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:40:41 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:40:42 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_exists(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] != ';' && !ft_strchr(SPACE, s[i]))
			return (1);
		i++;
	}
	return (0);
}

int	empty_cmd(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (!cmd_exists(arr[i]))
		{
			ft_printf("syntax error near unexpected token ';'\n");
			ft_tabfree(arr);
			return (1);
		}
		i++;
	}
	return (0);
}
