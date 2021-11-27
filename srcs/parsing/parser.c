/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:06:26 by astucky           #+#    #+#             */
/*   Updated: 2021/11/27 17:37:15 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

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

void	check_expansion(t_token *tok)
{
	print_token(tok);
	check_quotes(tok);
	print_token(tok);
	join_cell_tok(tok);
	egal_exp(tok);
	print_token(tok);
}

void	parser(t_pipe **pipe)
{
	t_token	*tok;
	char	*s;

	tok = NULL;
	s = get_last_input();
	lexer(&tok, s);
	if (!find_error(tok))
	{
		check_expansion(tok);
		complet_pipeline(pipe, tok);
	}
	clear_tok(tok);
}
