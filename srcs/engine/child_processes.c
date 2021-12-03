/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:02:59 by astucky           #+#    #+#             */
/*   Updated: 2021/12/03 17:07:00 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	first_child(t_pipe *p, t_global *g)
{
	if (p->in)
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	if (p->out)
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	else
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "fd_out");
	close(g->pipe_fd[0]);
}

void	mid_child(t_pipe *p, t_global *g, const int prev)
{
	if (p->in)
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	else
		dup_close(prev, STDIN_FILENO, "fd_in");
	if (p->out)
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	else
		dup_close(g->pipe_fd[1], STDOUT_FILENO, "fd_out");
	close(g->pipe_fd[0]);
}

void	last_child(t_pipe *p, t_global *g, const int prev)
{
	if (p->in)
		dup_close(p->fd_in, STDIN_FILENO, "fd_in");
	else
		dup_close(prev, STDIN_FILENO, "fd_in");
	if (p->out)
		dup_close(p->fd_out, STDOUT_FILENO, "fd_out");
	close(g->pipe_fd[0]);
	close(g->pipe_fd[1]);
}
