/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/01 18:27:00 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	child_process(t_pipe *p, t_global *g, const int prev, pid_t pid, size_t i)
{
	print_pipe(p);
	// if (!p->in)
	if (i < g->nb_proc - 1 && !p->in)
	{
		printf("in -- false: dup&close #%d\n", prev);
		dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
	}
	else if (p->in)
	{
		printf("in -- true: dup&close #%d\n", p->fd_in);
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	}
	else if (i == g->nb_proc - 1)
	{
		printf("in -- false: dup&close #%d\n", prev);
		dup_close(g->pipe_fd[1], STDIN_FILENO, "Pipe_fd[0]");
	}
	if (i < g->nb_proc - 1 && !p->out)
	{
		printf("out -- false: dup&close #%d\n", g->pipe_fd[1]);
		dup_close(g->pipe_fd[0], STDOUT_FILENO, "Pipe_fd[0]");
	}
	else if (p->out)
	{
		printf("in -- true: dup&close #%d\n", p->fd_out);
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	}
	close(g->pipe_fd[1]);
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

/*
static void	child_process(t_pipe *p, t_global *g, const int prev, pid_t pid)
{
	print_pipe(p);
	(void)g;
	(void)prev;
	// printf("in -- false: dup&close #%d\n", prev);
	// dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
	printf("out -- false: dup&close #%d\n", g->pipe_fd[1]);
	dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
	// close(g->pipe_fd[1]);
	if (p->in)
	{
		printf("Child -- in=true: dup&close #%d\n", p->fd_in);
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	}
	if (p->out)
	{
		printf("Child -- out=true: dup&close #%d\n", p->fd_out);
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	}
	// print_pipe(p);
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
*/

static void	daddy_process(t_pipe *p, t_global *g, const int prev, size_t i)
{
	// if (i < g->nb_proc - 1 && !p->in)
	if (!p->in)
	{
		printf("Daddy : close prev #%d\n", prev);
		if (close(prev) < 0)
			ft_err("Pipe_fd[0]", 8);
	}
	else if (p->in)
	{
		printf("Daddy : close fd_in #%d\n", p->fd_in);
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (i < g->nb_proc - 1 && !p->out)
	{
		printf("Daddy : close pipepefd[1] #%d\n", g->pipe_fd[1]);
		if (close(g->pipe_fd[1]) < 0)
			ft_err("Pipe_fd[1]", 14);
	}
	else if (p->out)
	{
		printf("Daddy : close fd_out #%d\n", p->fd_out);
		if (close(p->fd_out) < 0)
			ft_err("fd_out", 8);
	}
}

static void exec_jobs(t_pipe *p, t_global *g, size_t i)
{
	const int	prev_in = g->pipe_fd[0];
	pid_t		pid;

	// if (!p->out)
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
