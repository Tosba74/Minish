/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:41:15 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/21 20:18:37 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*ssrc;
	unsigned char		*sdst;

	ssrc = (const unsigned char *)src;
	sdst = (unsigned char *)dst;
	i = -1;
	if (src == NULL && dst == NULL)
		return (NULL);
	if (ssrc == sdst)
		return (dst);
	while (++i < n)
		sdst[i] = ssrc[i];
	return ((void *)sdst);
}
