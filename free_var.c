/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:41:24 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 17:04:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_empty_tab(char **arr)
{
	if (!arr[0])
		ft_tabfree(arr);
	return (0);
}

void	free_var(t_mini **sh)
{
	if ((*sh)->env)
		ft_tabfree((*sh)->env);
	free(*sh);
	*sh = NULL;
}
