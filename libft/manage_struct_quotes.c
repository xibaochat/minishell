/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_struct_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:41:18 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 17:41:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	char_is_double_quote(t_quo *q)
{
	if (q->double_quote)
	{
		q->have_quote = 0;
		q->double_quote = 0;
	}
	else
	{
		q->have_quote = 1;
		q->double_quote = 1;
	}
}

void		manage_struct_quotes(t_quo *q, const char *str, int i)
{
	char	c;

	c = str[i];
	if (c == DOUBLE && !q->single_quote && !is_escapted(q, str, i))
		char_is_double_quote(q);
	if (c == SINGLE && !q->double_quote && !is_escapted(q, str, i))
	{
		if (q->single_quote)
		{
			q->have_quote = 0;
			q->single_quote = 0;
		}
		else
		{
			q->have_quote = 1;
			q->single_quote = 1;
		}
	}
}
