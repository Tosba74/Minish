/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:46:07 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/14 13:06:25 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_env(t_global *g)
{
	t_env	*cpy;

	cpy = g->env;
	if (g->env == NULL)
		dprintf(STDERR_FILENO, "\033[32mSHIT! g->env is NULL, Bro!\033[0m\n");
	while (cpy->next)
	{
		dprintf(STDERR_FILENO, "\033[32m|%s| = |%s|\033[0m\n",
			cpy->name, cpy->value);
		cpy = cpy->next;
	}
}

void	print_env_teub(t_global *g)
{
	char	**env;

	dprintf(STDERR_FILENO, "\033[34m----- ENV_teub -----\033[0m\n");
	env = NULL;
	if (g->env == NULL)
		dprintf(STDERR_FILENO, "\033[31mg->env is NULL, Bro!\031[0m\n");
	else
		env = get_env_teub(g->env);
	print_envp(env);
}

void	print_hidden(t_global *g)
{
	t_env	*cpy;

	cpy = g->hidden;
	dprintf(STDERR_FILENO, "\033[34m----- HIDDEN_ENV -----\033[0m\n");
	if (g->hide_mod == false)
		dprintf(STDERR_FILENO, "\033[31mHide mode is off, Bro!\033[0m\n");
	if (cpy == NULL)
		dprintf(STDERR_FILENO, "\033[31mg->hidden is NULL, Bro!\033[0m\n");
	else
	{
		while (cpy)
		{
			dprintf(STDERR_FILENO, "|%s| = |%s|\n", cpy->name, cpy->value);
			cpy = cpy->next;
		}
	}
}

void	print_story(t_global *g)
{
	t_story	*history;

	history = g->history;
	dprintf(STDERR_FILENO, "\033[34m-----  HISTORY  ------\033[0m\n");
	if (g->history == NULL)
		dprintf(STDERR_FILENO, "\033[31mg->history is NULL, Bro!\033[0m\n");
	while (history)
	{
		dprintf(STDERR_FILENO, "\033[33m#%u\033[0m\t\033[32m%s\033[33m\n",
			history->index, history->cmd);
		history = history->next;
	}
}

void	print_token(t_global *g)
{
	t_token	*cpy;

	cpy = g->tok;
	if (!cpy)
		dprintf(STDERR_FILENO, "\033[31mg->token is NULL, Bro!\033[0m\n");
	while (cpy != NULL)
	{
		dprintf(STDERR_FILENO, "\033[033| V=|%s|  |type = %d|\n| next = %p\n",
			cpy->value, cpy->type, cpy->next);
		cpy = cpy->next;
	}
}
