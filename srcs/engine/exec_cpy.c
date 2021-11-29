/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/29 21:37:52 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	child_process(t_pipe *p, t_global *g, const int prev, pid_t pid)
{
	if (p->in)
		dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
	else
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	if (p->out)
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	if (p->job->is_cmd)
	{
		execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
		ft_err("EXECVE ERROR: ", 5);
		exit(pid);
	}
	else if (p->job->is_built)
	{
		g_err = select_built(p);
		exit(g_err);
	}
}

static void	daddy_process(t_pipe *p, t_global *g, const int prev)
{
	if (p->in)
	{
		if (close(prev) < 0)
			ft_err("Pipe_fd[0]", 8);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (p->out)
	{
		if (close(g->pipe_fd[1]) < 0)
			ft_err("Pipe_fd[1]", 8);
	}
	else
	{
		if (close(p->fd_out) < 0)
			ft_err("fd_out", 8);
	}
}

static void exec_jobs(t_pipe *p, t_global *g)
{
	const int	prev_in = g->pipe_fd[0];
	pid_t		pid;

	if (p->out)
		if (pipe(g->pipe_fd) < 0)
			ft_err("ExecJobs: ", 3);
	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 4);
	if (pid == 0)
		child_process(p, g, prev_in, pid);
	else
	{
		get_pid_exec()->pids[get_pid_exec()->index++] = pid;
		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
		daddy_process(p, g, prev_in);
	}
}

void	exec(t_global *g, t_pipe *pipe)
{
	int		i;
	t_pipe	*p;

	i = -1;
	g->nb_proc = 0;
	g->nb_proc = count_cell_pipe(pipe);
	printf("%zu\n", g->nb_proc);
	p = pipe;
	if (g->nb_proc == 1)
	{
		print_pipe(pipe);
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
			print_pipe(p);
			exec_jobs(p, g);
			p = p->next;
		}
		g_err = waiting_pid();
	}
}