/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 11:50:14 by xinwang           #+#    #+#             */
/*   Updated: 2019/10/18 11:50:17 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *head;

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		(*del)((*lst)->content);
		head = (*lst)->next;
		(*lst)->next = NULL;
		free(*lst);
		*lst = head;
	}
}
