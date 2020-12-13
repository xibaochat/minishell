/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:40:33 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 17:31:54 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_mini *sh, char **arr)
{
	int	i;

	i = -1;
	if (arr && ft_tablen(arr) > 1)
	{
		sh->last_return = 127;
		ft_printf("env : ‘%s’: No such file or directory\n", arr[1]);
	}
	else if (sh->env)
	{
		while ((sh->env)[++i])
		{
			if (sh->has_env_i
				&& !ft_strcmp((sh->env)[i], BASIC_ENV_PATH))
				continue;
			else if ((sh->env)[i][0] && has_equal_sign(sh->env[i]))
			{
				ft_putstr((sh->env)[i]);
				ft_putstr("\n");
			}
		}
		sh->last_return = 0;
	}
}

/*
** "export" alone outputs same as "env"
*/

void	ft_export_alone(char **arr, t_mini *sh)
{
	if (ft_tablen(arr) == 1)
		print_sort_env(sh->env, sh);
	else if (arr[1] && arr[1][0] == '-')
	{
		show_error_message("export:no option allowed\n", NULL, sh);
		return ;
	}
}

void	add_variables_in_env(t_mini *sh)
{
	char *path;
	char *tmp;

	path = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", path);
	free_str(path);
	path = tmp;
	ft_envadd(path, sh);
	ft_envadd("LS_COLORS=", sh);
	ft_envadd("_=/usr/bin/env", sh);
	ft_envadd("LESSCLOSE=/usr/bin/lesspipe %s %s", sh);
	ft_envadd("LESSOPEN=| /usr/bin/lesspipe %s", sh);
	ft_envadd(BASIC_ENV_PATH, sh);
	ft_envadd("OLDPWD", sh);
	ft_envadd("SHLVL=1", sh);
}

int		len_var_name(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '=' && !(var[i] == '+' && var[i + 1] == '='))
		i++;
	return (i);
}

int		is_new_var(char *s, char **env)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (s[i] && s[i] != '=' && s[i] != '+')
		i++;
	while (env[j] && (ft_strncmp(s, env[j], i)
							|| (len_var_name(env[j]) != len_var_name(s))))
		j++;
	if (!env[j])
		return (1);
	return (0);
}
