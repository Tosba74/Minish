/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/27 19:59:09 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	dollar_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;
	char	*value;
	t_env	*cpy;

	i = 1;
	if (input[i] == '?')
	{
		addback_cell_tok(tok,
			new_cell_tok(ft_itoa(g_err), ARG));
		return (2);
	}
	while (input[i] && is_name_env(input[i]))
		i++;
	tmp = ft_substr(input, 1, i - 1);
	cpy = env_find_cell(get_var_env(), tmp);
	if (cpy)
		value = cpy->value;
	else
		value = "";
	addback_cell_tok(tok,
		new_cell_tok(ft_strdup(value), ARG));
	ft_memdel(tmp);
	return (i);
}

int	quote_tok(t_token **tok, char *input)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_substr(input, 0, 1);
	while (input[++i])
	{
		if (input[i] == input[0])
		{
			if (input[0] == '\'')
				addback_cell_tok(tok,
					new_cell_tok(ft_substr(input, 1, i - 1), QUOTE));
			else if (input[0] == '"')
				addback_cell_tok(tok,
					new_cell_tok(ft_substr(input, 1, i - 1), DQUOTE));
			ft_memdel(tmp);
			return (i + 1);
		}
	}
	addback_cell_tok(tok,
		new_cell_tok(tmp, ERROR));
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
		new_cell_tok(ft_strdup(" "), SPC));
	return (i);
}

int	pipe_tok(t_token **tok, char *input)
{
	int		i;
	t_token	*last;

	last = last_cell_tok(*tok);
	i = 1;
	if (last->type == PIPE)
		last->type = ERROR;
	else if (last->type == SPC)
	{
		ft_memdel(last->value);
		last->value = ft_strdup("|");
		last->type = PIPE;
	}
	else
	{
		addback_cell_tok(tok,
			new_cell_tok(ft_strdup("|"), PIPE));
	}
	while (input[i] && input[i] == ' ')
		i++;
	return (i);
}
