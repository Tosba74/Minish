/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:21:26 by astucky           #+#    #+#             */
/*   Updated: 2021/11/12 18:49:37 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	newlen(char *s)
{
	int	ret;
	int	i;
	int	in_quotes;

	i = 0;
	ret = 0;
	in_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			in_quotes++;
		else if (s[i] == '$' && in_quotes % 2 == 0)
		{
		}
	}
	return (ret);
}
char	*dollar(char *s)
{
	int		in_quotes;
	int		i;
	char	*ret;
	char	*var;

	i = 0;
	ret = wrmalloc(sizeof(char) * (newlen(s) + 1));
	while (s[i])
	{
		if (s[i] == '$')

	}
	return (ret);
}
