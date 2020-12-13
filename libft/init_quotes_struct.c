/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_quotes_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <pnielly@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:39:44 by user42            #+#    #+#             */
/*   Updated: 2020/12/13 17:39:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_quo	init_quotes_struct(void)
{
	t_quo	quo;

	quo.have_quote = 0;
	quo.double_quote = 0;
	quo.single_quote = 0;
	return (quo);
}
