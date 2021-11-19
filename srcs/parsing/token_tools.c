/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/18 23:04:08 by astucky          ###   ########lyon.fr   */
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

void	join_cell_tok(t_token *tok)
{
	t_token	*second;

	while (tok)
	{
		if ((tok->type == ARG || (9 < tok->type && tok->type < 14))
			&& (tok->next && (tok->next->type < 3)))
		{
			second = tok->next;
			tok->value = ft_strjoin_free(tok->value, second->value, 3);
			tok->next = second->next;
			if (tok->next)
				tok->next->prev = tok;
			ft_memdel(second);
		}
		else
			tok = tok->next;
	}
}

void	remove_cell_tok(t_token *tok)
{
	t_token	*prev;
	t_token	*next;

	prev = tok->prev;
	next = tok->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	wrfree(tok->value);
	wrfree(tok);
}
