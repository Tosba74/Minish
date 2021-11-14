/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:21:26 by astucky           #+#    #+#             */
/*   Updated: 2021/11/14 16:26:21 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	varlen(char *s)
{
	int		i;
	char	*name;
	char	*ret;

	i = 0;
	while (s[i] && !is_spec_char(s[i]))
		i++;
	name = wrmalloc(sizeof(char) * (i));
	i = 1;
	while (s[i] && !is_spec_char(s[i]))
	{
		name[i - 1] = s[i];
		i++;
	}
	name[i - 1] = 0;
	ret = search_in_env(name);
	wrfree(name);
	return (ft_strlen(ret));
}

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
		{
			ret++;
			i++;
			in_quotes++;
		}
		else if (s[i] == '$' && in_quotes % 2 == 0)
		{
			ret += varlen(s + i);
			while (s[i + 1] && !is_spec_char(s[i + 1]))
				i++;
		}
		ret++;
		i++;
	}
	return (ret);
}

static void	replace_w_value(char *in, char *out)
{
	char	*var;
	int		i;
	int		i2;
	char	*value;

	i = 1;
	while (in[i] && !is_spec_char(in[i]))
		i++;
	var = wrmalloc(sizeof(char) * (i + 1));
	i = 1;
	while (in[i] && !is_spec_char(in[i]))
	{
		var[i - 1] = in[i];
		i++;
	}
	var[i - 1] = 0;
	value = search_in_env(var);
	wrfree(var);
	i2 = 0;
	i = ft_strlen(out);
	while (value[i2])
	{
		out[i] = value[i2];
		i++;
		i2++;
	}
}

char	*dollar(char *s)
{
	int		in_quotes;
	int		i;
	int		i2;
	char	*ret;

	i = 0;
	i2 = 0;
	in_quotes = 0;
	ret = wrmalloc(sizeof(char) * (newlen(s) + 1));
	ft_bzero(ret, newlen(s) + 1);
	while (s[i])
	{
		if (s[i] == '$' && in_quotes % 2 == 0)
		{
			replace_w_value(s + i, ret + i);
			i++;
			while (s[i] && !is_spec_char(s[i]))
				i++;
			while (ret[i2])
				i2++;
		}
		else if (s[i] == '\'')
			in_quotes++;
		else
		{
			ret[i2] = s[i];
			i++;
			i2++;
		}

	}
	return (ret);
}
