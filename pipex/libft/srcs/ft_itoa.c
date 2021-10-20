/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:31:30 by bmangin           #+#    #+#             */
/*   Updated: 2021/04/26 16:06:39 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(long nb, int len, char *res)
{
	res[len] = nb % 10 + '0';
	if (nb > 9)
		ft_recursive(nb / 10, len - 1, res);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*result;

	nb = (long)n;
	len = ft_len_num(n, 10);
	result = NULL;
	result = wrmalloc(len + 1);
	if (n < 0)
	{
		result[0] = '-';
		nb = -nb;
	}
	ft_recursive(nb, len - 1, result);
	return (result);
}
