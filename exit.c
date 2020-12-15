/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:40:56 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:40:57 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
	}
	return (0);
}

static int	ft_check_exit(char **s)
{
	if (s[1] && ft_strlen(s[1]) > 20)
		return (1);
	if ((s[1][0] != '+' && s[1][0] != '-' && !ft_isdigit(s[1][0]))
		|| has_alpha(&s[1][1]))
		return (1);
	if ((s[1][0] == '+' || s[1][0] == '-') && !s[1][1])
		return (1);
	if (s[1][0] == '-' && ft_atoi(s[1]) > 0)
		return (1);
	return (0);
}

int			arg_is_all_vide(char **split_input)
{
	int i;

	i = 1;
	while (split_input[i])
	{
		if (!split_input[i][0])
			i++;
		else
			return (0);
	}
	return (1);
}

void		ft_exit(char **split_input, t_mini *sh)
{
	int	tab_len;

	tab_len = ft_tablen(split_input);
	if (arg_is_all_vide(split_input) || tab_len == 1)
	{
		ft_tabfree(sh->env);
		exit(EXIT_SUCCESS);
	}
	else if (ft_check_exit(split_input))
	{
		ft_printf("exit\nbash: line 1: exit: %s: ", split_input[1]);
		ft_printf("numeric argument required\n");
		exit(2);
	}
	else if (tab_len > 2)
	{
		ft_putstr("exit\n");
		ft_putstr_fd("bash: line 1: exit: too many arguments\n", 2);
		sh->last_return = 1;
	}
	else
	{
		ft_putstr("exit\n");
		exit(ft_atoi(split_input[1]));
	}
}
