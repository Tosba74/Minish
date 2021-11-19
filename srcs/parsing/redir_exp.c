/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/19 03:25:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	try_open(char *path, t_type type)
{
	if (type == REDIR_R)
		return (open(path, O_CREAT | O_RDWR | O_TRUNC, 0644));
	if (type == REDIR_RD)
		return (open(path, O_CREAT | O_RDWR | O_APPEND, 0644));
	if (type == REDIR_L)
		return (open(path, O_RDONLY));
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

static void	replace_fd(int *old, int new, int default_fd)
{
	if (*old != default_fd)
		close(*old);
	*old = new;
}

static void	remove_redir_tok(t_token *tok)
{
	t_token	*next;

	next = tok->next;
	remove_cell_tok(tok);
	tok = next;
	while (tok && tok->type == SPC)
	{
		next = tok->next;
		remove_cell_tok(tok);
		tok = next;
	}
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

int	skip_redir(t_token *tok, t_pipe *pipe)
{
	int		new_fd;

	while (tok && tok->type != PIPE)
	{
		if (tok->type == REDIR_RD || tok->type == REDIR_L
			|| tok->type == REDIR_R)
		{
			new_fd = try_open(tok->value, tok->type);
			if (new_fd == -1 || !check_read(new_fd))
			{
				close_all_fd(pipe);
				return (0);
			}
			if (tok->type == REDIR_RD || tok->type == REDIR_R)
				replace_fd(&pipe->fd_out, new_fd, 1);
			else
				replace_fd(&pipe->fd_in, new_fd, 0);
			remove_redir_tok(tok);
		}
		else
			tok = tok->next;
	}
	return (1);
}