/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:43:20 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/14 12:54:06 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	is_spec_char(char c)
{
	int		i;
	char	*spec_char;

	i = -1;
	spec_char = "$\"'|?<>/@&";
	while (spec_char[++i])
		if (spec_char[i] == c)
			return (i);
	return (-1);
}

int	count_this_char(char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[++i])
		if (s[i] == c)
			counter++;
	return (counter);
}
