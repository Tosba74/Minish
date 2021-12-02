/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:30:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/02 18:29:55 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	daddy_exec(pid_t pid, t_pipe *p)
{
	get_pid_exec()->pids[get_pid_exec()->index++] = pid;
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
	g_err = waiting_pid();
	if (p->in)
		close(p->fd_in);
	if (p->out)
		close(p->fd_out);
}

int	b_exec(t_pipe *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 11);
	if (pid == 0)
	{
		if (p->in)
			dup2(p->fd_in, STDIN_FILENO);
		if (p->out)
			dup2(p->fd_out, STDOUT_FILENO);
		execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
		ft_err("EXECVE ERROR: ", 11);
		exit(pid);
	}
	else
		daddy_exec(pid, p);
	return (g_err);
}
