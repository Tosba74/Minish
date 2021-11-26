/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:46:07 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/26 22:26:10 by bmangin          ###   ########lyon.fr   */
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
		if (cpy->print != PRINT)
			dprintf(STDERR_FILENO, "\033[33m|%s| = |%s|\033[0m\n",
				cpy->name, cpy->value);
		cpy = cpy->next;
	}
}

void	print_env_teub(void)
{
	char	**env;

	dprintf(STDERR_FILENO, "\033[34m----- ENV_teub -----\033[0m\n");
	env = get_env_teub(*get_var_env(), 2);
	print_envp(env, 1);
}

void	print_hidden(void)
{
	t_env	*cpy;

	cpy = *get_var_env();
	if (cpy == NULL)
		dprintf(STDERR_FILENO, "\033[32mSHIT! g_g->env is NULL, Bro!\033[0m\n");
	while (cpy->next)
	{
		if (cpy->print == PAPRINT)
			dprintf(STDERR_FILENO, "\033[33m|%s| = |%s|\033[0m\n",
				cpy->name, cpy->value);
		cpy = cpy->next;
	}
}

void	print_pipestruct(t_pipe *p)
{
	t_pipe	*pipe_line;
	int		i;

	pipe_line = p;
	while (pipe_line)
	{
		i = -1;
		dprintf(STDERR_FILENO, "|%d|%d|\n", pipe_line->fd_in, pipe_line->fd_out);
		dprintf(STDERR_FILENO, "%s\n", pipe_line->job->job);
		while (pipe_line->job->av[++i])
			dprintf(STDERR_FILENO, "\t* %s\n", pipe_line->job->av[i]);
		pipe_line = pipe_line->next;
	}
}
