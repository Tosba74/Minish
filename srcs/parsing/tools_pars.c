/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:43:20 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/08 02:26:15 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	is_spec_char(char c)
{
	int		i;
	char	*convert;

	i = -1;
	convert = PARS_SHIT;
	while (convert[++i])
		if (convert[i] == c)
			return (i);
	return (-1);
}
