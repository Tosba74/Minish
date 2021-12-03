/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:05:51 by astucky           #+#    #+#             */
/*   Updated: 2021/12/03 23:31:04 by bmangin          ###   ########lyon.fr   */
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
	while (tok)
	{
		new = new_cell_pipe(tok);
		if (have_redir(tok))
			ret = skip_redir(new, tok);
		new->job = new_job(tok);
		if (ret == -1)
			get_pid_exec()->no_job = true;
		else if (!ret && new->heredoc)
		{
			new->save_in = dup(STDIN_FILENO);
			here_doc(new->job, new->heredoc);
		}
		addback_cell_pipe(pipe, new);
		next_pipe(&tok);
	}
}
