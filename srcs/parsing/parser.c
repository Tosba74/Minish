/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/17 19:28:42 by bmangin          ###   ########lyon.fr   */
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

void	complet_pipeline(t_global *g, t_token *tok)
{
	(void)g;
	print_token(tok);
}

void	parser(t_global *g)
{
	t_token	*tok;
	char	*input;

	tok = NULL;
	input = get_last_input(g);
	lexer(&tok, input);
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
