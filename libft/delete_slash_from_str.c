/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_slash_from_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:50:43 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 17:51:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_len_wo_extra_slash(char *s)
{
	int	i;
	int	nb_slash;
	int	j;

	i = 0;
	j = 0;
	nb_slash = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			while (s[i] && s[i] == '\\')
			{
				i++;
				nb_slash++;
				j++;
			}
		}
		else
			i++;
	}
	if (nb_slash % 2)
		return (i - j + (nb_slash / 2) + 1);
	return (i - j + (nb_slash / 2));
}

void	copy_part_str_wo_slash(char *s, int *i, char *new, int *j)
{
	int	nb_slash;
	int	k;

	nb_slash = 0;
	while (s[*i] && s[*i] == '\\')
	{
		(*i)++;
		nb_slash++;
	}
	if (nb_slash % 2)
		k = (nb_slash + 1) / 2;
	else
		k = nb_slash / 2;
	while (k--)
		new[(*j)++] = '\\';
}

void	copy_wo_slash(char *new, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\\')
			new[j++] = s[i++];
		else
			copy_part_str_wo_slash(s, &i, new, &j);
	}
}

void	delete_slash_from_str(char **s)
{
	char	*new;
	int		final_len;

	final_len = get_len_wo_extra_slash(*s);
	new = ft_strnew(final_len + 1);
	copy_wo_slash(new, *s);
	free_str(*s);
	*s = new;
}
