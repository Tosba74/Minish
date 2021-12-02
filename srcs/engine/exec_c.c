/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/02 09:36:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	child_process(t_pipe *p, t_global *g, const int prev, pid_t pid)
{
		
}

static void	daddy_process(t_pipe *p, t_global *g, const int prev)
{
}

static void exec_jobs(t_pipe *p, t_global *g, size_t i)
{
	const int	prev_in = g->pipe_fd[0];
	pid_t		pid;

	printf("debut de pipe pipe_fd #%d\n", prev_in);
	if (i < g->nb_proc - 1 && !p->out)
	{
		if (pipe(g->pipe_fd) < 0)
			ft_err("ExecJobs: ", 3);
		else
			printf("PIPE OK");
	}
	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 4);
	if (pid == 0)
		child_process(p, g, prev_in, pid, i);
	else
	{
		get_pid_exec()->pids[get_pid_exec()->index++] = pid;
		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
		daddy_process(p, g, prev_in, i);
	}
	printf("fin de pipe pipe_fd #%d\n", g->pipe_fd[0]);
}

void	exec(t_global *g, t_pipe *pipe)
{
	size_t	i;
	t_pipe	*p;

	i = -1;
	printf("%zu\n", g->nb_proc);
	p = pipe;
	if (g->nb_proc == 1)
	{
		if (pipe->job->is_cmd)
			g_err = b_exec(pipe);
		else if (p->job->is_built)
			g_err = select_built(pipe);
		// close_all_fd(pipe);
	}
	else
	{
		while (p)
		{
			++i;
			// print_pipe(p);
			exec_jobs(p, g, i);
			p = p->next;
		}
		g_err = waiting_pid();
	}
}
