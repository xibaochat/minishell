/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_export_var_val.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:39:29 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:39:31 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_invalid_char_in_env_name(char *str)
{
	int	i;

	i = 0;
	if (!i && (str[i] == '=' || ft_isdigit(str[i])))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (str[i] && str[i + 1] && str[i] == '+')
	{
		if (str[i + 1] == '=')
			return (0);
		return (1);
	}
	return (0);
}

int	has_equal_sign(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && i)
			return (1);
		i++;
	}
	return (0);
}
