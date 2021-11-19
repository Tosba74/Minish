/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/19 01:34:18 by bmangin          ###   ########lyon.fr   */
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

void	join_cell_tok(t_token *t)
{
	t_token	*second;

	while (t)
	{
		if ((((9 < t->type && t->type < 14) || t->type < 3)
			&& is_builtin(t->value) == -1 && (t->next && (t->next->type < 3))))
		{
			second = t->next;
			t->value = ft_strjoin_free(t->value, second->value, 3);
			t->next = second->next;
			if (t->next)
				t->next->prev = t;
			ft_memdel(second);
		}
		// else if (is_builtin(t->value) != -1)
			// t->type = BUILTIN;
		else
			t = t->next;
	}
}
