/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:06:26 by astucky           #+#    #+#             */
/*   Updated: 2021/12/03 17:21:52 by astucky          ###   ########lyon.fr   */
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
	check_quotes(tok);
	join_cell_tok(tok);
	egal_exp(tok);
	if (get_pid_exec()->no_job == true)
		clear_tok(tok);
}

void	parser(t_pipe **pipe, char *input, unsigned int *i)
{
	t_token	*tok;
	char	*s;

	tok = NULL;
	addback_cell_history(get_history(),
		new_cell_history(skip_space(input), (*i)++));
	s = get_last_input();
	lexer(&tok, skip_space(input));
	if (!find_error(tok))
	{
		print_token(tok);
		check_expansion(tok);
		if (tok)
			complet_pipeline(pipe, tok);
	}
	clear_tok(tok);
}
