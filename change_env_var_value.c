/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:39:07 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:39:08 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cherche ENV VAR exists or not, and return its index in the ENV
*/

int		get_matched_var_in_env(char **env, char *var)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (i);
	}
	return (-1);
}

void	go_to_required_directory(t_mini *sh, char *dest, char *src)
{
	char	*pwd;

	if (chdir(dest) == -1)
	{
		cd_error_message(dest);
		sh->last_return = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		change_env_var_value(sh->env, src, ENV_OLDPWD, sh);
		change_env_var_value(sh->env, pwd, ENV_PWD, sh);
		sh->last_return = 0;
		free_str(pwd);
	}
	free_str(dest);
}

void	change_env_var_value(char **env, char *new_v, char *varname, t_mini *sh)
{
	int		i;
	char	*tmp;
	char	*s;

	tmp = NULL;
	i = get_matched_var_in_env(env, varname);
	s = ft_strnew(ft_strlen(varname) + ft_strlen(new_v) + 1);
	ft_strncat(s, varname, ft_strlen(varname));
	if (new_v)
		ft_strncat(s, new_v, ft_strlen(new_v));
	if (i != -1)
	{
		tmp = env[i];
		env[i] = s;
		free_str(tmp);
	}
	else
		ft_envadd(s, sh);
}
