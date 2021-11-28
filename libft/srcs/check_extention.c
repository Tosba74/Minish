/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extention.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:40:20 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/28 15:20:08 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_extention(char *s, char *ext)
{
	char	*cmp;

	if (!ft_strrchr(s, 46))
		return (FAILURE);
	cmp = ft_strdup(ft_strrchr(s, 46));
	if (ft_strncmp(cmp, ext, 4))
	{
		wrfree(cmp);
		return (FAILURE);
	}
	wrfree(cmp);
	return (SUCCESS);
}
