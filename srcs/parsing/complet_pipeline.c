/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:14:05 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/19 01:01:25 by bmangin          ###   ########lyon.fr   */
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
	// new->fd_in = STDIN_FILENO;
	// new->fd_out = STDOUT_FILENO;
	// new->in = false;
	// new->out = false;
	new->job->av = complet_av(tok);
	// if (skip_redir(pipe, tok) == 1)
	// {
	// }
	
	
	//ne pas faire ca cest pour compile
	print_token(tok);
	// av = join_all_tok(tok);
	(void)pipe;
	addback_cell_pipe(pipe, new);
	// print_pipe(*pipe);
}
