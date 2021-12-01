/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:04:53 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/30 17:06:24 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(char **strs, int size)
{
	int	i;

	i = 0;
	if (!size)
		size = ft_strslen(strs);
	while (i != size)
		wrfree(strs[i++]);
	wrfree(strs);
}
