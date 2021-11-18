/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:56:40 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/17 22:48:08bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	egal_exp(t_token *tok)
{
	char	*content[2];
	t_token	*before;
	t_token	*after;

	before = tok;
	while (before && before->type != EGAL)
		before = before->next;
	if (before && before->type == EGAL)
	{
		after = before->next;
		before = before->prev;
		content[0] = before->value;
		content[1] = after->value;
		addback_cell_env(get_var_env(), new_cell_env(content, PAPRINT));
	}
}

static void	dollar_exp(t_token *tok)
{
	int		i;
	int		j;
	char	*tmp;
	t_token	*tok_tmp;

	i = 0;
	tok_tmp = NULL;
	while (tok->value[i] && tok->value[i] != '$')
		i++;
	j = dollar_tok(&tok_tmp, tok->value + i);
	tmp = ft_substr(tok->value, 0, i);
	tmp = ft_strjoin_free(tmp, tok_tmp->value, 3);
	tmp = ft_strjoin_free(tmp, tok->value + i + j, 3);
	tok->value = tmp;
	tok->type = ARG;
	wrfree(tok_tmp);
}

void	check_quotes(t_token *token)
{
	int		i;
	t_token	*tok;

	i = -1;
	tok = token;
	while (tok)
	{
		if (tok->type == DQUOTE || (9 < tok->type && tok->type < 14))
			while (ft_isinstr(tok->value, '$'))
				dollar_exp(tok);
		else if (tok->type == QUOTE)
			tok->type = ARG;
		tok = tok->next;
	}
}

char	*join_all_tok(t_token *tok)
{
	char	*s;

	if (!tok)
		return (NULL);
	if (!tok->next)
		return (tok->value);
	s = ft_strjoin_free(tok->value, tok->next->value, 1);
	tok = tok->next;
	while (tok->next)
	{
		if (tok->next->type == PIPE)
			return (s);
		s = ft_strjoin_free(s, tok->next->value, 3);
		tok = tok->next;
	}
	return (s);
}
