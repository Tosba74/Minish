/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/30 13:27:45 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*
void exec_builtin(t_pipe *p, t_global *g, int prev)
{
	if (!p->in && g->nb_proc > 1)
	{
		if (close(prev) < 0)
			ft_err("Pipe_fd[0]", 14);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 14);
	}
	if (!p->out && g->nb_proc > 1)
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	g_err = select_built(p);
	close(p->fd_out);
}
*/

static void child_process(t_pipe *p, t_global *g, const int prev, pid_t pid)
{
	if (g->nb_proc > 1)
	{
		if (!p->in)
		{
			dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
			printf("in-false prev= %d\n", prev);
			close(p->fd_in);
		}
		else
		{
			dup_close(p->fd_in, STDIN_FILENO, "fd_in");
			printf("in-true fd_in= %d\n", p->fd_in);
			close(prev);
		}
		if (!p->out)
		{
			dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
			printf("in-false pipe_fd= %d\n", g->pipe_fd[1]);
		}
		else
		{
			dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
			printf("in-true fd_out = %d\n", p->fd_out);
		}
		if (p->job->is_cmd)
		{
			printf("COMMAND\n");
			execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
			ft_err("EXECVE ERROR: ", 11);
			exit(pid);
		}
		// else
		// {
		// 	printf("BUILTIN\n");
		// 	g_err = select_built(p);
		// 	exit(g_err);
		// }
	}
}

/*
static void child_process(t_pipe *p, t_global *g, const int prev, pid_t pid)
{
	if (g->nb_proc > 1)
	{
		if (!p->in)
		{
			dup_close(p->fd_in, STDIN_FILENO, "fd_in");
		}
		if (!p->out)
		{
			dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
		}
		dup_close(prev, STDIN_FILENO, "Pipe_fd[0]");
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "Pipe_fd[1]");
		if (p->job->is_cmd)
		{
			printf("COMMAND\n");
			execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
			ft_err("EXECVE ERROR: ", 11);
		}
		else
		{
			printf("BUILTIN\n");
			g_err = select_built(p);
			exit(pid);
			exit(g_err);
		}
	}
}
*/

static void daddy_process(t_pipe *p, t_global *g, const int prev)
{
	if (g->nb_proc > 1)
	{
		if (!p->in)
		{
			if (close(prev) < 0)
				ft_err("Pipe_fd[0]", 14);
		}
		else
		{
			if (close(p->fd_in) < 0)
				ft_err("fd_in", 14);
		}
		if (!p->out)
		{
			if (close(g->pipe_fd[1]) < 0)
				ft_err("Pipe_fd[1]", 14);
		}
		else
		{
			if (close(p->fd_out) < 0)
				ft_err("fd_out", 14);
		}
	}
}

static void exec_jobs(t_pipe *p, t_global *g)
{
	const int prev_in = g->pipe_fd[0];
	pid_t pid;

	if (g->nb_proc > 1)
		if (pipe(g->pipe_fd) < 0)
			ft_err("ExecJobs: ", 10);
	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 11);
	if (pid == 0)
		child_process(p, g, prev_in, pid);
	else
	{
		get_pid_exec()->pids[get_pid_exec()->index++] = pid;
		signal(SIGINT, &handler);
		signal(SIGQUIT, &handler);
		if (!p->job->is_cmd)
			g_err = select_built(p);
		daddy_process(p, g, prev_in);
	}
}

/*
static void exec_jobs(t_pipe *p, t_global *g)
{
	const int	prev_in = g->pipe_fd[0];
	pid_t		pid;

	if (g->nb_proc > 1)
		if (pipe(g->pipe_fd) < 0)
			ft_err("ExecJobs: ", 10);
	if (p->job->is_cmd)
	{
		pid = fork();
		if (pid < 0)
			ft_err("ExecJobs: ", 11);
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
	else
		g_err = select_built(p);
}
*/

void exec(t_global *g, t_pipe *pipe)
{
	int i;
	t_pipe *p;

	i = -1;
	g->nb_proc = count_cell_pipe(pipe);
	printf("%zu\n", g->nb_proc);
	p = pipe;
	if (g->nb_proc == 1)
	{
		print_pipe(pipe);
		if (p->job->is_cmd)
			g_err = b_exec(pipe);
		else if (p->job->is_built)
			g_err = select_built(pipe);
		g_err = select_built(pipe);
		close_all_fd(pipe);
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
