/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maobe <maobe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 21:19:05 by maobe             #+#    #+#             */
/*   Updated: 2020/10/02 21:19:08 by maobe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}