/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/26 16:50:36 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*
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
		dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
	else
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	if (out)
		dup_close(p->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
	ft_err("EXECVE ERROR", 12);
}

static void	daddy_process(t_pipe *p, bool in, bool out, const int prev)
{
	if (in)
	{
		if (close(prev) < 0)
			ft_err("Pipe_fd[0]", 8);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (out)
	{
		if (close(p->pipe_fd[1]) < 0)
			ft_err("Pipe_fd[1]", 8);
	}
	else
	{
		if (close(p->fd_out) < 0)
			ft_err("fd_out", 8);
	}
}

static void	exec_jobs(t_global *g, t_pipe *p, bool in, bool out)
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
		g->pid_ar[g->nb_proc++] = pid;
		daddy_process(p, in, out, prev_in);
	}
}

int	exec(t_global *g, t_pipe *pipe)
{
	int		i;
	bool	in;
	bool	out;
	bool	is_built;
	t_pipe	*cpy;

	i = -1;
	in = true;
	out = true;
	is_built = false;
	cpy = pipe;
	while (++i < count_cell_pipe(cpy))
	{
		dprintf(STDERR_FILENO, "i => %d nb_proc => %zu\n", i, g->nb_proc);
		// if (is_built(av[1]))
		// 	is_built = true;
		g->env = get_env_teub(*get_var_env(), 1);
		if (cpy->fd_in != 0)
			in = false;
		if (cpy->fd_out != 1)
			out = false;
		// if (!cpy->job->job || !cpy->job->av)
			// ft_err("Command", 13);
		exec_jobs(g, cpy, in, out);
		cpy = cpy->next;
	}
	return (waiting_pid(g));
}
*/

static void	child_process(t_pipe *p, t_global *g, const int prev)
{
	if (!p->in)
		dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
	else
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	if (!p->out)
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	if (p->job->is_cmd)
	{
		execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
		ft_err("EXECVE ERROR: ", 11);
	}
	else
	{
		g_err = select_built(p);
		// t exit(g_err);
	}
}

static void	daddy_process(t_pipe *p, t_global *g, const int prev)
{
	if (!p->in)
	{
		if (close(prev) < 0)
			ft_err("Pipe_fd[0]", 8);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (!p->out)
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

void	exec_builtin(t_pipe *p, t_global *g, int prev)
{
	if (!p->in)
	{
		if (close(prev) < 0)
			ft_err("Pipe_fd[0]", 8);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (!p->out)
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	g_err = select_built(p);
	close(p->fd_out);
}

static void	exec_jobs(t_pipe *p, t_global *g)
{
	const int	prev_in = g->pipe_fd[0];
	pid_t		pid;

	if (!p->out)
		if (pipe(g->pipe_fd) < 0)
			ft_err("ExecJobs: ", 10);
	if (p->job->is_cmd)
	{
		pid = fork();
		if (pid < 0)
			ft_err("ExecJobs: ", 11);
		if (pid == 0)
			child_process(p, g, prev_in);
		else
		{
			g->pids[g->index++] = pid;
			daddy_process(p, g, prev_in);
		}
	}
	else
		exec_builtin(p, g, prev_in);
}

void	exec(t_global *g, t_pipe *pipe)
{
	int		i;
	t_pipe	*p;

	i = -1;
	p = pipe;
	while (p)
	{
		print_pipe(p);
		exec_jobs(p, g);
		p = p->next;
	}
	g_err = waiting_pid(g);
}
