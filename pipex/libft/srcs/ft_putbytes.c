/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbytes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 13:41:54 by bmangin           #+#    #+#             */
/*   Updated: 2021/08/17 18:15:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putbytes(int nb)
{
	if (nb == 1)
	{
		ft_putchar('1');
		return (SUCCESS);
	}
	else if (nb == 0)
	{
		ft_putchar('0');
		return (SUCCESS);
	}
	else
	{
		ft_putbytes(nb / 2);
		if ((nb % 2) > 0)
			ft_putchar('1');
		else
			ft_putchar('0');
	}
	return (FAILURE);
}
