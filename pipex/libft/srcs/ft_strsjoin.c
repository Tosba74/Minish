/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 15:44:33 by bmangin           #+#    #+#             */
/*   Updated: 2021/07/18 15:57:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsjoin(char **s1, char *s2)
{
	char	**strs;
	int		i;

	i = 0;
	strs = wrmalloc(sizeof(char *) * (ft_strslen(s1) + 2));
	if (s1)
	{
		while (s1[i])
		{
			strs[i] = ft_strdup(s1[i]);
			i++;
		}
	}
	strs[i++] = ft_strdup(s2);
	strs[i] = NULL;
	free_all(s1, ft_strslen(s1));
	wrfree(s2);
	return (strs);
}
