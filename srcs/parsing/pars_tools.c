/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 01:43:20 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/15 21:49:49 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	*find_error(t_token *tok)
{
	t_token	*cpy;

	cpy = tok;
	while (cpy)
	{
		if (cpy->type == ERROR)
			return (ft_strjoin(cpy->value, " :"));
		cpy = cpy->next;
	}
	return (NULL);
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
