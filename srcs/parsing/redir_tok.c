/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/16 19:27:59 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	rredir_tok(t_token **token, char *input)
{
	bool	append;
	int		i;

	i = 1;
	append = 0;
	if (input[i] == '>')
	{
		append = 1;
		i++;
	}
	if (input[i] == '<' || input[i] == '>')
	{
		ft_err("too much redirection identifiers", 8);
		return (0);
	}
	if (append)
		addback_cell_tok(token, new_cell_tok(ft_strdup(">>"), DRREDIR));
	else
		addback_cell_tok(token, new_cell_tok(ft_strdup(">"), RREDIR));
	return (i);
}

int	lredir_tok(t_token **token, char *input)
{
	bool	append;
	int		i;

	i = 1;
	append = 0;
	if (input[i] == '<')
	{
		append = 1;
		i++;
	}
	if (input[i] == '<' || input[i] == '>')
	{
		ft_err("too much redirection identifiers", 8);
		return (0);
	}
	if (append)
		addback_cell_tok(token, new_cell_tok(ft_strdup("<<"), DLREDIR));
	else
		addback_cell_tok(token, new_cell_tok(ft_strdup("<"), LREDIR));
	return (i);
}
