/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 01:03:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/05/30 14:06:31 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		j;
	size_t	l;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (haystack[i] && len > 0)
	{
		j = 0;
		l = 0;
		while (l < len && haystack[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i);
			l++;
		}
		i++;
		len--;
	}
	return (NULL);
}
