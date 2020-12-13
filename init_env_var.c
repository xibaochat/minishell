/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:42:41 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:42:42 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	init_env_var(t_mini *sh)
{
	char	*path;
	char	*new_path;
	char	*arr[3];
	int		i;

	i = -1;
	arr[0] = ENV_OLDPWD;
	arr[1] = ENV_PWD;
	arr[2] = NULL;
	path = getcwd(NULL, 0);
	while (++i < 2 && sh->fst_init == 1)
	{
		if (!ft_find_env(arr[i], sh->env))
		{
			new_path = ft_strnew(ft_strlen(arr[i]) + ft_strlen(path) + 1);
			ft_strcat(new_path, arr[i]);
			ft_strcat(new_path, path);
			ft_envadd(new_path, sh);
			free_str(new_path);
		}
	}
	sh->fst_init = 0;
	free_str(path);
}
