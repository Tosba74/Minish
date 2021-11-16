/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/16 18:56:37 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	quote_tok(t_token **tok, char *input)
{
	int		i;
	char	c;

	i = 0;
	c = input[0];
	while (input[++i])
	{
		if (input[i] == c)
		{
			if (c == '\'')
				addback_cell_tok(tok,
					new_cell_tok(ft_substr(input, 1, i - 1), QUOTE));
			else if (c == '"')
				addback_cell_tok(tok,
					new_cell_tok(ft_substr(input, 1, i - 1), DQUOTE));
			return (i + 1);
		}
	}
	addback_cell_tok(tok,
		new_cell_tok("NULL", ERROR));
	return (1);
}

int	egal_tok(t_token **tok, char *input)
{
	(void)input;
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup("="), EGAL));
	return (1);
}

int	pipe_tok(t_token **tok, char *input)
{
	int		i;
	t_token	*last;

	last = last_cell_tok(*tok);
	i = 0;
	if (input[i] == '|')
	{
		if (last->type == PIPE)
			ft_err("Double pipe", 5);
		else if (last->type == SPC)
		{
			ft_memdel(last->value);
			ft_memdel(last);
		}
		addback_cell_tok(tok,
			new_cell_tok(ft_strdup("|"), PIPE));
		while (input[i++])
			if (!ft_isspace(input[i]))
				break ;
	}
	return (i);
}

int	space_tok(t_token **tok, char *input)
{
	int		i;

	i = -1;
	while (input[++i])
		if (!ft_isspace(input[i]))
			break ;
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(" "), SPC));
	return (i);
}
