/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/15 01:43:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_token	*new_cell_tok(char *content, t_type t)
{
	t_token	*tok;

	tok = wrmalloc(sizeof(t_token));
	tok->value = content;
	tok->type = t;
	tok->prev = NULL;
	tok->next = NULL;
	return (tok);
}

t_token	*last_cell_tok(t_token *tok)
{
	if (tok == NULL)
		return (NULL);
	while (tok->next != NULL)
		tok = tok->next;
	return (tok);
}

void	addback_cell_tok(t_token **tok, t_token *new)
{
	t_token	*last;

	last = last_cell_tok(*tok);
	if (!last)
		*tok = new;
	else
	{
		last->next = new;
		new->prev = last;
	}
}

void	join_cell_tok(t_token **tok)
{
	t_token	*tmp;

	while ((*tok))
	{
		if ((*tok)->type == ARG && (*tok)->next && ((*tok)->next->type <= 2))
		{
			tmp = (*tok)->next;
			if (!tmp && !tmp->value)
				(*tok)->value = ft_strjoin_free((*tok)->value, tmp->value, 3);
			(*tok)->next = tmp->next;
			wrfree(tmp);
			if ((*tok)->next)
				(*tok)->next->prev = (*tok);
		}
		else
			(*tok) = (*tok)->next;
	}
}

void	clear_tok(t_token *tok)
{
	t_token	*actu;
	t_token	*next;

	actu = tok;
	next = actu->next;
	while (next != NULL)
	{
		ft_memdel(actu->value);
		ft_memdel(actu);
		actu = next;
		next = actu->next;
	}
	ft_memdel(actu->value);
	ft_memdel(actu);
}
