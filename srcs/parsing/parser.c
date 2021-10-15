/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/14 12:58:14 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	create_tok(t_global *g, char *input)
{
	int		(*pf_tok[6])(t_global *g, char *input);

	pf_tok[0] = &add_tok_var;
	pf_tok[1] = &tok_cote;
	pf_tok[2] = &tok_cote;
	pf_tok[3] = &pipe_tok;
	pf_tok[4] = &redir_tok;
	pf_tok[5] = &redir_tok;
	return (pf_tok[is_spec_char(*input)](g, input));
}

void	lexer(t_global *g)
{
	char	*input;
	int		i;

	input = get_last_input(g);
	i = -1;
	while (input[++i])
	{
		if (is_spec_char(input[i]) != -1)
			i += create_tok(g, input + i);
		else
			ft_putchar(input[i]);
	}
	ft_putchar('\n');
}

void	complet_pipeline(t_global *g)
{
	print_token(g);
}

void	parser(t_global *g)
{
	lexer(g);
	complet_pipeline(g);
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
