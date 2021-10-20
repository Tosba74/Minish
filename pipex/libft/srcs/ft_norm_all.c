/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:45:13 by bmangin           #+#    #+#             */
/*   Updated: 2021/04/26 16:08:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_norm_all(void **s, size_t count, size_t size)
{
	if (count < 0 || size < 0)
		return (1);
	*s = (void *)wrmalloc(count * size);
	if (!(*s))
		return (1);
	ft_bzero(*s, count * size);
	return (0);
}
