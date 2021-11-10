/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:46:07 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/10 17:10:28 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_env(void)
{
	t_env	*cpy;

	cpy = *get_var_env();
	if (cpy == NULL)
		dprintf(STDERR_FILENO, "\033[32mSHIT! g_g->env is NULL, Bro!\033[0m\n");
	while (cpy->next)
	{
		if (cpy->print == PRINT)
			dprintf(STDERR_FILENO, "\033[32m|%s| = |%s|\033[0m\n",
				cpy->name, cpy->value);
		else
			dprintf(STDERR_FILENO, "\033[33m|%s| = |%s|\033[0m\n",
				cpy->name, cpy->value);

		cpy = cpy->next;
	}
}

void	print_env_teub(void)
{
	char	**env;

	dprintf(STDERR_FILENO, "\033[34m----- ENV_teub -----\033[0m\n");
	env = NULL;
	if (g_g->env == NULL)
		dprintf(STDERR_FILENO, "\033[31mg_g->env is NULL, Bro!\031[0m\n");
	else
		env = get_env_teub(g_g->env);
	print_envp(env);
}

void	print_hidden(void)
{
	t_env	*cpy;

	cpy = g_g->hidden;
	dprintf(STDERR_FILENO, "\033[34m----- HIDDEN_ENV -----\033[0m\n");
	if (g_g->hide_mod == false)
		dprintf(STDERR_FILENO, "\033[31mHide mode is off, Bro!\033[0m\n");
	if (cpy == NULL)
		dprintf(STDERR_FILENO, "\033[31mg_g->hidden is NULL, Bro!\033[0m\n");
	else
	{
		while (cpy)
		{
			dprintf(STDERR_FILENO, "|%s| = |%s|\n", cpy->name, cpy->value);
			cpy = cpy->next;
		}
	}
}

void	print_story(void)
{
	t_story	*history;

	history = g_g->history;
	dprintf(STDERR_FILENO, "\033[34m-----  HISTORY  ------\033[0m\n");
	if (g_g->history == NULL)
		dprintf(STDERR_FILENO, "\033[31mg_g->history is NULL, Bro!\033[0m\n");
	while (history)
	{
		dprintf(STDERR_FILENO, "\033[33m#%u\033[0m\t\033[32m%s\033[33m\n",
			history->index, history->cmd);
		history = history->next;
	}
}

void	print_pipestruct(void)
{
	t_pipe	*pipe_line;
	int		i;

	pipe_line = g_g->pipe;
	while (pipe_line)
	{
		i = -1;
		dprintf(STDERR_FILENO, "%s\n", pipe_line->pipe_line);
		dprintf(STDERR_FILENO, "|%d|%d|\n", pipe_line->fd_in, pipe_line->fd_out);
		dprintf(STDERR_FILENO, "%s\n", pipe_line->job->job);
		dprintf(STDERR_FILENO, "%s\n", pipe_line->job->flags);
		while (pipe_line->job->av[++i])
			dprintf(STDERR_FILENO, "\t* %s\n", pipe_line->job->av[i]);
		pipe_line = pipe_line->next;
	}
}
