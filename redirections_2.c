/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:44:11 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 16:44:13 by pnielly          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		has_redirection_in_arr(char **arr)
{
	t_quo	q;
	int		i;
	int		j;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		q = init_quotes_struct();
		while (arr[i][++j])
		{
			manage_struct_quotes(&q, arr[i], j);
			if (arr[i][j] && is_redir_char(arr[i][j])
				&& !q.have_quote)
				return (1);
		}
	}
	return (0);
}

/*
** sticked_next_redir() checks if the next redirection
** is not separated from the first one
** in the original command.
** For example : "echo jojo>lulu>dodo"
*/

int		sticked_next_redir(char *str)
{
	int	i;

	i = 0;
	while (!ft_strchr("<>", str[i]) && str[i])
		i++;
	while (ft_strchr("<>", str[i]) && str[i])
		i++;
	while (!ft_strchr("<> ", str[i]) && str[i])
		i++;
	if (str[i] && str[i] != ' ')
		return (i);
	return (0);
}

/*
** new_cmd() returns the copy of the old cmd
** WITHOUT the redirection currently handled.
** For ex : new_cmd("echo jojo > lulu") = "echo jojo"
** For ex2 : new_cmd("echo jojo > lulu > dodo") = "echo jojo > dodo"
*/

void	new_cmd_2(char **arr, int i, int j, char **new)
{
	int	k;
	int	sticked;

	if (!new)
		return ;
	k = -1;
	while (++k < i)
		new[k] = ft_strdup(arr[k]);
	if (j)
		new[k++] = ft_substr(arr[i], 0, j);
	sticked = sticked_next_redir(arr[i]);
	if (sticked)
		new[k++] = ft_substr(arr[i], sticked, ft_strlen(arr[i]) - sticked);
	if (!arr[i][j + 1] || (arr[i][j + 1] == '>' && !arr[i][j + 2]))
		i += 2;
	else
		i++;
	while (arr[i])
		new[k++] = ft_strdup(arr[i++]);
	new[k] = NULL;
}

char	**new_cmd(char **arr, int i, int j)
{
	int		len;
	char	**new;
	int		sticked;

	len = (int)ft_tablen(arr);
	new = NULL;
	if ((!arr[i][j + 1] || (arr[i][j + 1] == '>'
				&& (!arr[i][j + 2]) && arr[i + 1])))
		len--;
	if (!j)
		len--;
	sticked = sticked_next_redir(arr[i]);
	if (sticked)
		len++;
	new = malloc(sizeof(char *) * (len + 1));
	new_cmd_2(arr, i, j, new);
	return (new);
}
