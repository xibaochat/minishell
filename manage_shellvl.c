/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shellvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:30 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/15 12:38:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strisdigit(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	manage_shellvl(t_mini *sh)
{
	char	*value;
	int		nb;
	char	*new_value;
	char	*nb_str;

	if (!sh->has_env_i)
	{
		value = ft_find_env("SHLVL=", sh->env);
		if (!value[0] || (value[0] == '=' && !value[1]))
			nb = 1;
		else if (value && (value + 1) && !ft_strisdigit(value + 1))
			nb = 1;
		else if (ft_atoi(value) < 0 || ft_atoi(value) >= 999)
		{
			if (ft_atoi(value) >= 999)
				ft_putstr_fd("shell level (1000) too high, resetting to 0\n",
						STDERR_FILENO);
			nb = 0;
		}
		else
			nb = ft_atoi(value) + 1;
		nb_str = ft_itoa(nb);
		new_value = ft_strjoin("SHLVL=", nb_str);
		free_str(nb_str);
		replace_var_value(new_value, sh->env);
		free_str(new_value);
	}
}
