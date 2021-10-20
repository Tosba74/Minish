/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 17:09:01 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	tokenizator(t_token **tok, char *input)
{
	int		(*pf_tok[8])(t_token **tok, char *input);

	pf_tok[0] = quote_tok;
	pf_tok[1] = quote_tok;
	pf_tok[2] = var_tok;
	pf_tok[3] = pipe_tok;
	pf_tok[4] = pipe_tok;
	pf_tok[5] = space_tok;
	pf_tok[6] = redir_tok;
	pf_tok[7] = redir_tok;
	return (pf_tok[is_spec_char(*input)](tok, input));
}

void	check_expansion(t_global *g, t_token *tok)
{
	/*
	void	(*pf_exp[3])(t_global *g, t_token *token);

	pf_exp[0] = dollar_exp;
	pf_exp[1] = egal_exp;
	pf_exp[2] = pipe_exp;
	*/
	(void)tok;
	(void)g;
}

void	lexer(t_token **tok, char *input)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
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

void	egal_exp(t_global *g, t_token *tok)
{
	char	*content[2];
	t_token	*before;
	t_token	*after;

	before = tok;
	content[0] = NULL;
	content[1] = NULL;
	while (before && before->type != EGAL)
		before = before->next;
	if (before->type != EGAL)
		return ;
	else
	{
		after = before->next;
		before = before->prev;
		content[0] = before->value;
		content[1] = after->value;
		addback_cell_env(&g->hidden, new_cell_env(content));
		tok = before->next;
		if (tok)
			tok->next = after->next;
		else
			tok = after->next;
	}
}

void	complet_pipeline(t_global *g, t_token *tok)
{
	print_token(tok);
	// check_expansion(g, tok);
	egal_exp(g, tok);
	dollar_exp(tok);
	printf("ENVPATH tu bug?:\n");
	printf("%s\n", select_env_path(tok->value, get_env_teub(g->env)));
}


void	parser(t_global *g)
{
	t_token	*tok;
	char	*input;

	tok = NULL;
	input = get_last_input(g);
	lexer(&tok, input);
	if (!find_error(tok))
		ft_err(g, "Syntax :", 5);
	complet_pipeline(g, tok);
	clear_tok(tok);
}
	// debug(g, 5);
	// dispath_jobs(g);
	// debug(g, 0);
	// debug(g, 1);
	// debug(g, 2);
	// debug(g, 3);
	// debug(g, 4);
	// teub = split(s, " ");
	// printf("teub[0] = %s\n teub[1] = %s\n", teub[0], teub [1]);
	// printf("CMD NOW = %s\n", s);
	// exec_cmd(teub);
// }
