/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:15:22 by bmangin           #+#    #+#             */
/*   Updated: 2021/08/17 18:15:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	waiting_pid(t_pipex *p)
{
	int	i;
	int	ret;
	int	wstatus;

	i = -1;
	while (++i < p->index)
	{
		waitpid(p->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			ret = (unsigned char)WEXITSTATUS(wstatus);
	}
	return (ret);
}

static void	child_process(t_pipex *p, const int prev)
{
	if (p->in)
		dup_close(prev, STDIN_FILENO, "Pipefd[0]");
	else
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	if (p->out)
		dup_close(p->pipefd[1], STDOUT_FILENO, "Pipefd[1]");
	else
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	execve(p->cmd, p->av, p->env);
	ft_err("EXECVE ERROR: ", 5);
}

static void	daddy_process(t_pipex *p, const int prev)
{
	if (p->in)
	{
		if (close(prev) < 0)
			ft_err("Pipefd[0]", 8);
	}
	else
	{
		if (close(p->fd_in) < 0)
			ft_err("fd_in", 8);
	}
	if (p->out)
	{
		if (close(p->pipefd[1]) < 0)
			ft_err("Pipefd[1]", 8);
	}
	else
	{
		if (close(p->fd_out) < 0)
			ft_err("fd_out", 8);
	}
}

static void	exec_jobs(t_pipex *p)
{
	const int	prev_in = p->pipefd[0];
	pid_t		pid;

	if (p->out)
		if (pipe(p->pipefd) < 0)
			ft_err("ExecJobs: ", 3);
	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 4);
	if (pid == 0)
		child_process(p, prev_in);
	else
	{
		p->pids[p->index++] = pid;
		daddy_process(p, prev_in);
	}
}

int	exec(t_pipex *p, int ac, char **av, char **env)
{
	int		i;

	i = 1;
	while (i++ < ac - 2)
	{
		p->env = env;
		init_bool(p, i, ac);
		init_cmd(p, av[i]);
		exec_jobs(p);
	}
	return (waiting_pid(p));
}
