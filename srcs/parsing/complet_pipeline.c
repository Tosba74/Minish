/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:14:05 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/29 00:57:25y bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	**complet_av(t_token *tok)
{
	int		i;
	int		count;
	char	**av;

	i = 0;
	count = count_cell_tok(tok);
	av = wrmalloc(sizeof(char *) * (count + 1));
	while (tok && tok->type != PIPE)
	{
		if (tok->type != SPC)
			av[i++] = ft_strdup(tok->value);
		tok = tok->next;
	}
	av[i] = NULL;
	return (av);
}

void	next_pipe(t_token **tok)
{
	while (*tok && (*tok)->type != PIPE)
		(*tok) = (*tok)->next;
	if (*tok)
		(*tok) = (*tok)->next;
}

int	have_redir(t_token *tok)
{
	while (tok && tok->type != PIPE)
	{
		if (9 < tok->type && tok->type < 14)
			return (1);
		tok = tok->next;
	}
	return (0);
}

void	complet_pipeline(t_pipe **pipe, t_token *tok)
{
	int		ret;
	t_pipe	*new;

	if (!tok)
		return ;
	ret = 0;
	printf("Apparament tok est pas null");
	while (tok)
	{
		new = new_cell_pipe(tok);
		if (have_redir(tok))
			ret = skip_redir(new, tok);
		if (ret != -1)
			new->job->av = complet_av(tok);
		if (new->heredoc && ft_strslen(new->job->av) == 1)
			here_doc(new->job, new->heredoc);
		addback_cell_pipe(pipe, new);
		next_pipe(&tok);
	}
}
