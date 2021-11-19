/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/19 01:17:10 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	try_open(char *path, t_type type)
{
	if (type == REDIR_R)
		return(open(path, O_CREAT | O_RDWR | O_TRUNC, 0644));
	if (type == REDIR_RD)
		return(open(path, O_CREAT | O_RDWR | O_APPEND, 0644));
	if (type == REDIR_L)
		return(open(path, O_RDONLY));
	return (-1);
}

static int	check_read(int fd)
{
	char	test[2];
	int		err;

	err = read(fd, test, 1);
	if (err == -1)
		return (0);
	return (1);
}

int	skip_redir(t_token *tok, t_pipe *pipe)
{
	t_token	*tcpy;
	t_pipe	*pcpy;
	int		new_fd;
	t_token *next;

	tcpy = tok;
	pcpy = last_cell_pipe(pipe);
	pcpy->fd_in = 0;
	pcpy->fd_out = 1;
	while (tcpy)
	{
		if (tcpy->type == REDIR_RD || tcpy->type == REDIR_L
				|| tcpy->type == REDIR_R)
		{
			new_fd = try_open(tcpy->value, tcpy->type);
			if (new_fd == -1 || !check_read(new_fd))
			{
				if (pcpy->fd_out != 1)
					close(pcpy->fd_out);
				if (pcpy->fd_in)
					close(pcpy->fd_in);
				return (0);
			}
			if (tcpy->type == REDIR_RD || tcpy->type == REDIR_R)
			{
				if (pcpy->fd_out != 1)
					close(pcpy->fd_out);
				pcpy->fd_out = new_fd;
			}
			else
			{
				if (pcpy->fd_in)
					close(pcpy->fd_in);
				pcpy->fd_in = new_fd;
			}
			next = tcpy->next;
			remove_cell_tok(tcpy);
			tcpy=next;
			while (tcpy && tcpy->type == SPC)
			{
				next = tcpy->next;
				remove_cell_tok(tcpy);
				tcpy=next;
			}
		}
		else
			tcpy = tcpy->next;
	}
	return (1);
}
