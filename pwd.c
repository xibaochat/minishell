/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:56 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:43:57 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_mini *sh)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		ft_putstr_w_new_line(strerror(errno));
	else
	{
		ft_putstr_w_new_line(path);
		free_str(path);
	}
	(void)sh;
}
