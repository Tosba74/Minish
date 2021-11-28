/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/28 18:36:26 by bmangin          ###   ########lyon.fr   */
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
	t_token	*next;

	while (tok)
	{
		next = tok->next;
		wrfree(tok->value);
		wrfree(tok);
		tok = next;
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
