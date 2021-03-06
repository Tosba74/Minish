/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:56:40 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 23:29:34 by bmangin          ###   ########lyon.fr   */
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
		get_pid_exec()->no_job = true;
		before = before->prev;
		if (before && before->type == SPC)
			before = before->prev;
		if (before && !ft_strncmp(before->value, "export", ft_strlen("export")))
			get_pid_exec()->no_job = false;
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
	t_token	*tok;

	tok = token;
	while (tok)
	{
		if (tok->type == DQUOTE)
			while (ft_isinstr(tok->value, '$'))
				dollar_exp(tok);
		else if (9 < tok->type && tok->type < 14)
			fucking_dollar(tok);
		else if (tok->type == QUOTE)
			tok->type = ARG;
		tok = tok->next;
	}
}

void	join_cell_tok(t_token *t)
{
	t_token	*second;

	while (t)
	{
		if (((9 < t->type && t->type < 14) || t->type < 3)
			&& is_builtin(t->value) == -1 && (t->next && (t->next->type < 3)))
		{
			second = t->next;
			t->value = ft_strjoin_free(t->value, second->value, 3);
			t->next = second->next;
			if (t->next)
				t->next->prev = t;
			wrfree(second);
		}
		else if ((9 < t->type && t->type < 14) && t->prev->type == SPC)
			remove_cell_tok(t->prev);
		else
			t = t->next;
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
