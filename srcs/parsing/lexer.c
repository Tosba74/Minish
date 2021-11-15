/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/15 14:05:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	dollar_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;
	char	*value;
	t_env	*cpy;

	i = 1;
	printf("|input=%s|\n", input);
	while (input[i] && is_spec_char(input[i] != -1))
		i++;
	tmp = ft_substr(input, 1, i - 1);
	cpy = env_find_cell(get_var_env(), tmp);
	if (cpy)
		value = cpy->value;
	else
		value = "";
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(value), ARG));
	wrfree(tmp);
	return (i + 1);
}

/*
int	dollar_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;
	char	*value;

	i = 1;
	while (input[i] && !is_spec_char(input[i]))
		i++;
	printf("avant malloc de %d\n", i);
	tmp = wrmalloc(sizeof(char) * i);
	i = 1;
	while (input[i] && !is_spec_char(input[i]))
	{
		tmp[i - 1] = input[i];
		i++;
	}
	tmp[i] = 0;
	printf("%s\n", tmp);
	value = ft_strdup(search_in_env(tmp));
	if (tmp && value)
		printf("%s = %s\n", tmp, value);
	addback_cell_tok(tok, new_cell_tok(value, ARG));
	wrfree(tmp);
	return (i);
}
*/

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
