/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:06:26 by astucky           #+#    #+#             */
/*   Updated: 2021/11/16 19:43:16 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

	/*
void	check_expansion(t_token *tok)
{
	void	(*pf_exp[3])(t_global *g, t_token *token);

	pf_exp[0] = dollar_exp;
	pf_exp[1] = egal_exp;
	pf_exp[2] = pipe_exp;
	(void)tok;
}
	*/

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

char	*search_in_env(char *var)
{
	t_env	*env;

	env = *get_var_env();
	while (env)
	{
		if (!ft_strcmp(env->name, var))
			return (env->value);
		env = env->next;
	}
	return ("\n");
}

void	dollar_exp(t_token *tok)
{
	t_token	*name;

	name = tok;
	while (name && name->type != DOLLAR)
		name = name->next;
	if (name && name->type == DOLLAR)
	{
		name->type = ARG;
		name->value = ft_strdup(search_in_env(name->value + 1));
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

void	complet_pipeline(t_pipe *pipe, t_token *tok)
{
	char	*av;

	//ne pas faire ca cest pour compile
	av = join_all_tok(tok);
	addback_cell_pipe(&pipe, new_cell_pipe(av, new_job(av)));
	// printf("%s\n", 	pipe->pipe_line);
}

void	check_expansion(t_token *tok)
{
	print_token(tok);
	egal_exp(tok);
	// dollar_exp(tok);
	join_cell_tok(&tok);
	// print_token(tok);
}

int	parser(t_pipe *pipe)
{
	t_token	*tok;
	char	*s;

	tok = NULL;
	s = get_last_input();
	if (!lexer(&tok, s))
	{
		clear_tok(tok);
		return (0);
	}
	if (find_error(tok))
		ft_err(find_error(tok), 5);
	else
	{
		check_expansion(tok);
		complet_pipeline(pipe, tok);
	}
	clear_tok(tok);
	return (1);
}
