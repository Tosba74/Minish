/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:04:53 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/16 01:41:12 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_all(char **strs, int size)
{
	int	i;

	i = 0;
	while (i != size)
		wrfree(strs[i++]);
	wrfree(strs);
}
