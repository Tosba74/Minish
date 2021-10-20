/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 16:20:42 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	dup_close(t_global *g, int src, int dst, char *s)
{
	if (dup2(src, dst) < 0)
		ft_err(g, s, 14);
	if (close (src) < 0)
		ft_err(g, s, 14);
}

static int	waiting_pid(t_global *g)
{
	int	i;
	int	ret;
	int	wstatus;

	i = -1;
	while (++i < (int)g->nb_proc)
	{
		waitpid(g->pid_ar[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			ret = (unsigned char)WEXITSTATUS(wstatus);
	}
	return (ret);
}

static void	child_process(t_global *g, bool in, bool out, const int prev)
{
	if (in)
		dup_close(g, prev, STDIN_FILENO, "Pipefd[0]");
	else
		dup_close(g, g->pipe->fd_in, STDIN_FILENO, "fd_in");
	if (out)
		dup_close(g, g->pipe->pipe_fd[1], STDOUT_FILENO, "Pipefd[1]");
	else
		dup_close(g, g->pipe->fd_out, STDOUT_FILENO, "fd_out");
	execve(g->pipe->job->job, g->pipe->job->av, g->envp);
	ft_err(g, "EXECVE ERROR: ", 12);
}

static void	daddy_process(t_global *g, bool in, bool out, const int prev)
{
	if (in)
	{
		if (close(prev) < 0)
			ft_err(g, "Pipefd[0]", 8);
	}
	else
	{
		if (close(g->pipe->fd_in) < 0)
			ft_err(g, "fd_in", 8);
	}
	if (out)
	{
		if (close(g->pipe->pipe_fd[1]) < 0)
			ft_err(g, "Pipefd[1]", 8);
	}
	else
	{
		if (close(g->pipe->fd_out) < 0)
			ft_err(g, "fd_out", 8);
	}
}

static void	exec_jobs(t_global *g, bool in, bool out)
{
	const int	prev_in = g->pipe->pipe_fd[0];
	pid_t		pid;

	if (out)
		if (pipe(g->pipe->pipe_fd) < 0)
			ft_err(g, "ExecJobs: ", 10);
	pid = fork();
	if (pid < 0)
		ft_err(g, "ExecJobs: ", 11);
	if (pid == 0)
		child_process(g, in, out, prev_in);
	else
	{
		g->pid_ar[g->nb_proc++] = pid;
		daddy_process(g, in, out, prev_in);
	}
}

int	exec(t_global *g)
{
	int		i;
	bool	in;
	bool	out;

	i = -1;
	in = true;
	out = true;
	while (++i < count_cell_pipe(g->pipe))
	{
		g->envp = get_env_teub(g->env);
		if (g->pipe->fd_in != 0)
			in = false;
		if (g->pipe->fd_out != 1)
			out = false;
		if (!g->pipe->job->job || !g->pipe->job->av)
			ft_err(g, "Command: ", 13);
		exec_jobs(g, in, out);
	}
	return (waiting_pid(g));
}
