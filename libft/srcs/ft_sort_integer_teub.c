/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:41:03 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/24 23:39:30 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_integer_teub(int *teub, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (teub[i] > teub[i + 1])
		{
			ft_swap(&teub[i], &teub[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}
