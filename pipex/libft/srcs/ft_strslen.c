/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 21:03:03 by bmangin           #+#    #+#             */
/*   Updated: 2021/07/16 19:26:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strslen(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return (0);
	while (strs[i] != NULL)
		i++;
	return (i);
}
