/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shellvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:30 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/14 15:49:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_shellvl(t_mini *sh)
{
	char	*value;
	int		nb;
	char	*new_value;
	char	*nb_str;

	if (!sh->has_env_i)
	{
		value = ft_find_env("SHLVL=", sh->env);
		if (ft_atoi(value) < 0 || ft_atoi(value) >= 999)
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
