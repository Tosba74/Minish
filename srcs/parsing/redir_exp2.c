/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:31:51 by astucky           #+#    #+#             */
/*   Updated: 2021/12/03 17:02:17 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	replace_fd(int *old, int new, int default_fd, bool *change)
{
	if (*old != default_fd)
		close(*old);
	*old = new;
	*change = true;
}

void	close_all_fd(t_pipe *pipe)
{
	if (pipe->fd_out != 1)
		close(pipe->fd_out);
	if (pipe->fd_in)
		close(pipe->fd_in);
	pipe->fd_out = 1;
	pipe->fd_in = 0;
	pipe->out = false;
	pipe->in = false;
}

int	open_redir(t_type type, char *path)
{
	if (type == REDIR_R)
		return (open(path, O_CREAT | O_RDWR | O_TRUNC, 0644));
	else if (type == REDIR_RD)
		return (open(path, O_CREAT | O_RDWR | O_APPEND, 0644));
	else if (type == REDIR_L)
		return (open(path, O_RDONLY));
	else
		return (1);
}
