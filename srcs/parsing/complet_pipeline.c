/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complet_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 00:14:05 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/21 22:32:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*
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
*/

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

void	complet_pipeline(t_pipe **pipe, t_token *tok)
{
	int		ret;
	t_pipe	*new;

	while (tok)
	{
		printf("Wesh mec!\n");
		new = new_cell_pipe(tok);
		ret = skip_redir(new, tok);
		printf("%d\n", ret);
		if (ret != -1)
		{
			print_token(tok);
			new->job->av = complet_av(tok);
			next_pipe(&tok);
			print_pipe(new);
		}
		else
		{
			printf("tu gere pas lerreur mec!\n");
			break ;
		}
	}
	addback_cell_pipe(pipe, new);
}
