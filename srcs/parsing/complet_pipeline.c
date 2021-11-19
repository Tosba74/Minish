/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:14:05 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/19 02:46:39 by astucky          ###   ########lyon.fr   */
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
	print_token(tok);
}

char **complet_av(t_token *tok)
{
	int		i;
	int		count;
	char	**av;

	i = 0;
	count = count_cell_tok(tok);
	av = wrmalloc(sizeof(char *) * (count + 1));	
	while (tok && tok->type == PIPE)
	{
		av[i++] = tok->value;
		tok = tok->next;
	}
	av[i] = NULL;
	return (av);
}
void	complet_pipeline(t_pipe **pipe, t_token *tok)
{
	t_pipe	*new;

	check_expansion(tok);
	// skip_redir(tok);
	new = new_cell_pipe(tok);
	new->next = 0;
	if (skip_redir(tok, new) == 1)
	{
		print_token(tok);
		new->job->av = complet_av(tok);
		print_pipe(new);
	}
	
	
	//ne pas faire ca cest pour compile
	// av = join_all_tok(tok);
	addback_cell_pipe(pipe, new);
}
