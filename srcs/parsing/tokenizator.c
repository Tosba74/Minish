/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/15 04:02:09 by bmangin          ###   ########lyon.fr   */
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

void clear_tok(t_token *tok)
{
	t_token	*actu;
	t_token	*last;

	actu = tok;
	last = actu->next;
	while (last)
	{
		ft_memdel(actu->value);
		ft_memdel(actu);
		actu = actu->next;
		last = actu->next;
	}
	ft_memdel(actu->value);
	ft_memdel(actu);
}
