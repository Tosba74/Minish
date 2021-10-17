/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:22:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/17 19:26:20 by bmangin          ###   ########lyon.fr   */
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
	// ft_err(g, "quote: ", 3);
	return (1);
}

int	var_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (input[++i] && !is_spec_char(input[i]))
		tmp[i] = input[i];
	tmp[i] = 0;
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(tmp), VAR));
	return (i);
}

int	pipe_tok(t_token **tok, char *input)
{
	if (input[0] == '|')
	{
		addback_cell_tok(tok,
			new_cell_tok(ft_strdup("|"), PIPE));
	}
	else if (input[0] == '=')
	{
		addback_cell_tok(tok,
			new_cell_tok(ft_strdup("="), EGAL));
	}
	return (1);
}

int	space_tok(t_token **tok, char *input)
{
	int		i;

	i = -1;
	while (input[++i])
		if (!ft_isspace(input[i]))
			break ;
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(" "), SPACE));
	return (i);
}

int	redir_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (input[++i] && input[i] == '>' && input[i] == '<')
		tmp[i] = input[i];
	tmp[i] = 0;
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(tmp), REDIR));
	return (i + 1);
}
