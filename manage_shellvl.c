/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_shellvl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:30 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:43:33 by pnielly          ###   ########.fr       */
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
		if (ft_atoi(value) < 0)
			nb = 0;
		else
			nb = ft_atoi(value) + 1;
		nb_str = ft_itoa(nb);
		new_value = ft_strjoin("SHLVL=", nb_str);
		free_str(nb_str);
		replace_var_value(new_value, sh->env);
		free_str(new_value);
	}
}
