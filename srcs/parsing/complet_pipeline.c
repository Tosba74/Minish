/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:14:05 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/18 01:10:33 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	check_exp(t_token *tok)
{
	while (tok)
	{
		printf("%d > ", tok->type);
		tok = tok->next;
	}
}

t_token	**split_pipe(t_token *tok)
{
	(void)tok;
	return (NULL);
}

void	check_expansion(t_token *tok)
{
	print_token(tok);
	check_quotes(tok);
	print_token(tok);
	egal_exp(tok);
	join_cell_tok(tok);
	skip_redir(tok);
	print_token(tok);
}

void	complet_pipeline(t_pipe *pipe, t_token *tok)
{
	char	*av;

	//ne pas faire ca cest pour compile
	check_expansion(tok);
	av = join_all_tok(tok);
	(void)pipe;
	addback_cell_pipe(&pipe, new_cell_pipe(av, new_job(av)));
	print_pipe(pipe);
}
