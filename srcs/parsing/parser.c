/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 02:00:38 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/12 15:00:01 by bmangin          ###   ########lyon.fr   */
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
	content[0] = NULL;
	content[1] = NULL;
	while (before && before->type != EGAL)
		before = before->next;
	if (before && before->type == EGAL)
	{
		// printf("La! ya un egal!\n");
		after = before->next;
		before = before->prev;
		printf("av>%sap>%s\n", before->value, after->value);
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
	return ("");
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
	addback_cell_pipe(&pipe, new_cell_pipe(join_all_tok(tok)));
	printf("%s\n", 	pipe->pipe_line);
}

void	check_expansion(t_token *tok)
{
	print_token(tok);
	egal_exp(tok);
	dollar_exp(tok);
	join_cell_tok(&tok);
	print_token(tok);
	// print_hidden();
	// printf("ENVPATH tu bug?:\n");
	// printf("%s\n", select_env_path(tok->value, get_env_teub(g->env)));
}

void	parser(t_pipe *pipe)
{
	t_token	*tok;
	char	*s;

	tok = NULL;
	s = get_last_input();
	lexer(&tok, s);
	if (find_error(tok))
		ft_err(find_error(tok), 5);
	else
	{
		check_expansion(tok);
		complet_pipeline(pipe, tok);
	}
	clear_tok(tok);
}
