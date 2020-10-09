/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_char_to_skip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:26:51 by xinwang           #+#    #+#             */
/*   Updated: 2019/11/29 14:55:02 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	skip_conversion_chars(char *format, int *i)
{
	while (format[*i] &&
	!is_conversion_char(format[*i]) &&
	format[*i] != '%')
		++(*i);
	++(*i);
}
