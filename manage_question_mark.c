/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_question_mark.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnielly <pnielly@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:43:24 by pnielly           #+#    #+#             */
/*   Updated: 2020/12/13 17:00:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** if the char apres $ is ?
*/

int		next_char_is_question_mark(char *s, int i)
{
	return (s[i + 1] && s[i + 1] == '?');
}

/*
** replace $? by exit value in the str
*/

void	replace_question_mark_by_exit_value(char **str, int i, int n)
{
	char	*s;
	int		nb_lens;
	char	*s1;

	s1 = NULL;
	s = NULL;
	nb_lens = 0;
	s1 = ft_itoa(n);
	nb_lens = get_nb_size(n);
	s = ft_strnew(ft_strlen(*str) - 1 + nb_lens);
	ft_strncat(s, *str, i);
	ft_strcat(s, s1);
	free_str(s1);
	if ((*str)[i + 2])
		ft_strncat(s, (*str) + i + 2, ft_strlen(*str) - i - 2);
	free_str(*str);
	*str = s;
}

void	manage_question_mark(char **str, int *i, int exit_value)
{
	replace_question_mark_by_exit_value(str, *i, exit_value);
	*i += get_nb_size(exit_value);
}
