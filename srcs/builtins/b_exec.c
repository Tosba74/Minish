/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:30:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/26 23:15:35 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int		b_exec(t_pipe *p)
{
	pid_t 		pid;

	pid = fork();
	if (pid < 0)
		ft_err("ExecJobs: ", 11);
	if (pid == 0)
	{
		execve(p->job->job, p->job->av, get_env_teub(*get_var_env(), 1));
		ft_err("EXECVE ERROR: ", 11);
	}
	else
	{
		get_pid_exec()->pids[get_pid_exec()->index++] = pid;
		if (p->in)
			close(p->fd_in);
		if (p->out)
			close(p->fd_out);
	}
	return (waiting_pid());
}
