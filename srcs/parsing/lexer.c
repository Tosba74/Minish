/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/12 18:41:31 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"
/*
int	dollar_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (input[++i] && !is_spec_char(input[i]))
		tmp[i] = input[i];
	tmp[i + 1] = 0;
	printf("tmp = %s\n", tmp);
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(tmp), DOLLAR));
	return (i);
}
*/
int	dollar_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;

	i = 0;
	while (input[i] && !is_spec_char(input[i]))
		i++;
	tmp = wrmalloc(sizeof(char) * i);
	i = 1;
	while (input[i] && !is_spec_char(input[i]))
	{
		tmp[i - 1] = input[i];
		i++;
	}
	tmp[i] = 0;
	addback_cell_tok(tok, new_cell_tok(ft_strdup(search_in_env(tmp)), ARG));
	wrfree(tmp);
	return (i);
}

int	is_spec_char(char c)
{
	int		i;
	char	*spec_char;

	i = -1;
	spec_char = "\"'$=| <>";
	while (spec_char[++i])
		if (spec_char[i] == c)
			return (i);
	return (-1);
}

static int	tokenizator(t_token **tok, char *input)
{
	int		(*pf_tok[8])(t_token **tok, char *input);

	pf_tok[0] = quote_tok;
	pf_tok[1] = quote_tok;
	pf_tok[2] = dollar_tok;
	pf_tok[3] = egal_tok;
	pf_tok[4] = pipe_tok;
	pf_tok[5] = space_tok;
	pf_tok[6] = redir_tok;
	pf_tok[7] = redir_tok;
	return (pf_tok[is_spec_char(*input)](tok, input));
}

void	lexer(t_token **tok, char *input)
{
	int		i;
	int		j;

	i = 0;
	while (input[i])
	{
		if (is_spec_char(input[i]) != -1)
			i += tokenizator(tok, input + i);
		else
		{
			j = i;
			while (input[i] && is_spec_char(input[i]) == -1)
				i++;
			addback_cell_tok(tok,
				new_cell_tok(ft_substr(input, j, i - j), ARG));
		}
	}
}
