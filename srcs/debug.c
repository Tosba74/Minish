/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 16:22:33 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	print_pipestruct(t_global *g)
{
	t_pipe	*pipe_line;
	int		i;

	pipe_line = g->pipe;
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

void	debug(t_global *g, int i)
{
	void	(*pf[5])(t_global *g);

	pf[0] = &print_env;
	pf[1] = &print_env_teub;
	pf[2] = &print_hidden;
	pf[3] = &print_story;
	pf[4] = &print_pipestruct;
	if (g->debug == true)
	{
		printf("debug activate\n");
		pf[i](g);
	}
}
