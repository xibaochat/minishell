/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinwang <xinwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 18:27:52 by xinwang           #+#    #+#             */
/*   Updated: 2019/10/18 04:16:54 by xinwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_lens;
	size_t	src_lens;
	size_t	meme;
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	dest_lens = ft_strlen(dst);
	src_lens = ft_strlen((char *)src);
	meme = size;
	while (dst[++i] && size)
		size--;
	if (!size)
		return (meme + src_lens);
	while (src[j] && size > 1)
	{
		dst[i++] = src[j++];
		size--;
	}
	dst[i] = '\0';
	return (dest_lens + src_lens);
}
