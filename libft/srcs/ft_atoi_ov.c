/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_ov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 00:58:11 by bmangin           #+#    #+#             */
/*   Updated: 2021/08/12 17:39:59 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_ov(long num, int neg, int len)
{
	if (len >= 10)
	{
		if (neg == 1 && num > 2147483647)
			return (-1);
		else if (neg == -1 && num > 2147483648)
			return (0);
	}
	return (num * neg);
}

int	ft_atoi_ov(const char *str)
{
	long	num;
	int		neg;
	int		len;

	num = 0;
	neg = 1;
	len = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str++ - '0');
		len++;
	}
	return (ft_check_ov(num, neg, len));
}
