/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fst_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:44:44 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:44:46 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "minishell.h"

void	exec_not_build_in_cmd(char *bin_path, char **arr, t_mini *sh)
{
	if (execve(bin_path, arr, sh->env) == -1)
	{
		sh->last_return = 126;
		ft_putstr_w_new_line_fd(strerror(errno), 2);
		exit(126);
	}
	free_str(bin_path);
}
