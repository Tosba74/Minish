/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/09 12:40:40 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

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

static void	child_process(t_pipe *p, bool in, bool out, const int prev)
{
	if (in)
		dup_close(prev, STDIN_FILENO, "Pipefd[0]");
	else
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	if (out)
		dup_close(p->pipe_fd[1], STDOUT_FILENO, "Pipefd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	execve(p->job->job, p->job->av, g_g->envp);
	ft_err("EXECVE ERROR", 12);
}

static void	daddy_process(t_pipe *p, bool in, bool out, const int prev)
{
	if (in)
	{
		if (close(prev) < 0)
			ft_err("Pipefd[0]", 8);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (out)
	{
		if (close(p->pipe_fd[1]) < 0)
			ft_err("Pipefd[1]", 8);
	}
	else
	{
		if (close(p->fd_out) < 0)
			ft_err("fd_out", 8);
	}
}

static void	exec_jobs(t_pipe *p, bool in, bool out)
{
	const int	prev_in = p->pipe_fd[0];
	pid_t		pid;

	if (out)
		if (pipe(p->pipe_fd) < 0)
			ft_err("ExecJobs", 10);
	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs", 11);
	if (pid == 0)
		child_process(p, in, out, prev_in);
	else
	{
		g_g->pid_ar[g_g->nb_proc++] = pid;
		daddy_process(p, in, out, prev_in);
	}
}

int	exec(t_pipe *pipe)
{
	int		i;
	bool	in;
	bool	out;
	t_pipe	*cpy;

	(void)pipe;
	i = -1;
	in = true;
	out = true;
	cpy = g_g->pipe;
	while (++i < count_cell_pipe(cpy))
	{
		dprintf(STDERR_FILENO, "i => %d nb_proc => %zu\n", i, g_g->nb_proc);
		g_g->envp = get_env_teub(g_g->env);
		if (cpy->fd_in != 0)
			in = false;
		if (cpy->fd_out != 1)
			out = false;
		if (!cpy->job->job || !cpy->job->av)
			ft_err("Command", 13);
		exec_jobs(cpy, in, out);
		cpy = cpy->next;
	}
	return (waiting_pid(g_g));
}
