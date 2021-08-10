/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:59:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/04/29 18:58:55 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	dst = wrmalloc(sizeof(char) * (size + 1));
	ft_memcpy(dst, s1, size + 1);
	return (dst);
}
