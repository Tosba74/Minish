/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/15 04:38:26 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	redir_tok(t_global *g, char *input)
{
	(void)g;
	(void)input;
	return (1);
}

int	var_tok(t_global *g, char *input)
{
	int		i;

	i = 0;
	input++;
	if (input[i] == '\0')
	{
		ft_putchar('$');
		return (1);
	}
	if (input[i] == '?')
	{
		printf("comment jreturn l'ancien process?\n");
		i++;
		return (2);
	}
	while (ft_isdefine(input[i]))
		i++;
	
	(void)g;
	return (0);
}

int	egal_tok(t_global *g, char *input)
{
	(void)g;
	(void)input;
}

int	pipe_tok(t_global *g, char *input)
{
	t_tok	*tmp;

	tmp = last_cell_tok(g->tok);
	if (tmp->type == SPACE)
		tmp->type = PIPE;
	if (tmp->prev->type == PIPE)
		ft_err(g, "Syntax: ", 5);
	(void)g;
	(void)input;
	return (1);
}

int	space_tok(t_global *g, char *input)
{
	int		i;
	t_tok	*last;

	i = -1;
	last = last_cell_tok(g->tok);
	while (input[++i])
		if (input[i] != ' ')
			break ;
	if (last)
	addback_cell_tok(&g->tok, new_cell_tok(NULL, SPACE));
	return (i);
}

int	quote_tok(t_global *g, char *input)
{
	int		i;
	char	c;
	char	*s;

	i = 0;
	c = input[0];
	input++;
	while (input[++i])
	{
		if (input[i] == c)
		{
			addback_cell_tok(&g->tok,
				new_cell_tok(ft_strdup(input, 0, i), QUOTE));
			return (i);
		}
	}
	ft_err(g, "quote: ", 3);
	return (1);
}
