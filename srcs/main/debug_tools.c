/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 20:46:07 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 20:24:49 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_env(void)
{
	t_env	*cpy;

	cpy = *get_var_env();
	if (cpy == NULL)
		printf("\033[32mSHIT! g_g->env is NULL, Bro!\033[0m\n");
	while (cpy->next)
	{
		if (cpy->print == PRINT)
			printf("\033[32m|%s| = |%s|\033[0m\n",
				cpy->name, cpy->value);
		if (cpy->print != PRINT)
			printf("\033[33m|%s| = |%s|\033[0m\n",
				cpy->name, cpy->value);
		cpy = cpy->next;
	}
}

void	print_env_teub(void)
{
	char	**env;

	printf("\033[34m----- ENV_teub -----\033[0m\n");
	env = get_env_teub(*get_var_env(), 2);
	print_envp(env, 1);
}

void	print_hidden(void)
{
	t_env	*cpy;

	cpy = *get_var_env();
	if (cpy == NULL)
		printf("\033[32mSHIT! g_g->env is NULL, Bro!\033[0m\n");
	while (cpy->next)
	{
		if (cpy->print == PAPRINT)
			printf("\033[33m|%s| = |%s|\033[0m\n",
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
		printf("|%d|%d|\n", pipe_line->fd_in, pipe_line->fd_out);
		printf("%s\n", pipe_line->job->job);
		while (pipe_line->job->av[++i])
			printf("\t* %s\n", pipe_line->job->av[i]);
		pipe_line = pipe_line->next;
	}
}

void	print_pipe(t_pipe *p)
{
	t_pipe	*cpy;
	int		i;

	cpy = p;
	i = -1;
	printf("|  cmd = %28s |\n", cpy->job->job);
	while (cpy->job->av[++i])
		printf("| av[%d]  %28s |\n", i, cpy->job->av[i]);
	printf("| is_cmd = %3d      is_built = %3d    |\n",
		cpy->job->is_cmd, cpy->job->is_built);
	printf("| bool_in = %3d     bool_ out = %3d   |\n", cpy->in, cpy->out);
	printf("| fd_in = %3d       fd_ out = %3d     |\n", cpy->fd_in, cpy->fd_out);
}
