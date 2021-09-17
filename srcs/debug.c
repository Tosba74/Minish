/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/17 16:54:09 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	print_env(t_global *g)
{
	t_env	*cpy;

	cpy = g->env;
	if (g->env == NULL)
		dprintf(STDERR_FILENO, "\033[34mSHIT! g->env is NULL, Bro!\033[0m\n");
	while (cpy->next)
	{
		dprintf(STDERR_FILENO, "\033[34m|%s| = |%s|\033[0m\n", cpy->name, cpy->value);
		cpy = cpy->next;
	}
}

static void	print_env_tab(t_global *g)
{
	char	**env;

	dprintf(STDERR_FILENO, "\033[34m----- ENV_TAB -----\033[0m\n");
	env = get_env_tab(g->env);
	print_envp(env);
}

static void	print_hidden(t_global *g)
{
	t_env	*cpy;

	cpy = g->hidden;
	dprintf(STDERR_FILENO, "\033[34m----- HIDDEN_ENV -----\033[0m\n");
	if (g->hide_mod == false)
		dprintf(STDERR_FILENO, "\033[34mHide mode is off, Bro!\033[0m\n");
	if (cpy == NULL)
		dprintf(STDERR_FILENO, "\033[34mg->hidden is NULL, Bro!\033[0m\n");
	while (cpy->next)
		dprintf(STDERR_FILENO, "|%s| = |%s|\n", cpy->name, cpy->value);
}

void	debug(t_global *g, int i)
{
	void	(*pf[3])(t_global *g);

	pf[0] = &print_env;
	pf[1] = &print_env_tab;
	pf[2] = &print_hidden;
	if (g->debug == true)
		pf[i](g);
}
