/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 20:16:28 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	child_process(t_pipe *p, t_global *g, const int prev, size_t i)
{
	if (i == 0)
		first_child(p, g);
	else if (i != g->nb_proc - 1)
		mid_child(p, g, prev);
	else
		last_child(p, g, prev);
	if (p->job->is_cmd)
	{
		g_err = execve(p->job->job, p->job->av,
				get_env_teub(*get_var_env(), 1));
		ft_err("EXECVE ERROR: ", 11);
		exit(g_err);
	}
	else if (p->job->is_built)
	{
		g_err = select_built(p);
		exit(g_err);
	}
}

static void	daddy_process(t_pipe *p, t_global *g, const int prev, size_t i)
{
	if (i != 0)
		close(prev);
	close(g->pipe_fd[1]);
	if (p->in)
		close(p->fd_in);
	if (p->out)
		close(p->fd_out);
	if (p->heredoc)
	{
		dup2(p->save_in, STDIN_FILENO);
		close(p->save_in);
	}
}

static void	exec_jobs(t_pipe *p, t_global *g, size_t i)
{
	const int	prev_in = g->pipe_fd[0];
	pid_t		pid;

	if (i < g->nb_proc - 1 && !p->out)
		if (pipe(g->pipe_fd) < 0)
			ft_err("ExecJobs: ", 10);
	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 12);
	if (pid == 0)
		child_process(p, g, prev_in, i);
	else
	{
		get_pid_exec()->pids[get_pid_exec()->index++] = pid;
		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
		daddy_process(p, g, prev_in, i);
	}
}

void	exec(t_global *g, t_pipe *pipe)
{
	size_t	i;
	t_pipe	*p;

	i = -1;
	p = pipe;
	if (g->nb_proc == 1)
	{
		if (pipe->job->is_cmd)
			g_err = b_exec(pipe);
		else if (p->job->is_built)
			g_err = select_built(pipe);
	}
	else
	{
		while (p)
		{
			++i;
			exec_jobs(p, g, i);
			p = p->next;
		}
		g_err = waiting_pid();
	}
}
