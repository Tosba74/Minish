/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:54:59 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/17 19:58:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		new = wrmalloc(sizeof(char));
		if (!new)
			return (NULL);
		new = ft_strdup("");
		return (new);
	}
	new = wrmalloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s + start, len);
	new[len] = 0;
	return (new);
}
