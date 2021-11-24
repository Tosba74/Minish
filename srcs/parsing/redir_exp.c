/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/24 15:53:32 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	remove_redir_tok(t_token **tok)
{
	t_token	*next;

	next = (*tok)->next;
	remove_cell_tok(*tok);
	*tok = next;
	while (*tok && (*tok)->type == SPC)
	{
		next = (*tok)->next;
		remove_cell_tok(*tok);
		*tok = next;
	}
}

static int	check_perm(t_type type, mode_t st_mode)
{
	if (!st_mode)
		return (1);
	if (type == REDIR_L && !(st_mode & S_IRUSR))
		return (0);
	if ((type == REDIR_R || type == REDIR_RD) && !(st_mode & S_IWUSR))
		return (0);
	return (1);
}

static int	try_open(t_token *tok, char *path)
{
	struct stat	buf;
/*	int			create;

	create = access(path, F_OK);
	buf.st_mode = 0;
	if (!create)
		stat(token->value, &buf);
	printf("dire = %d\n", (bool)(buf.st_mode & S_IFDIR));
	printf("usrr = %d\n", (bool)(buf.st_mode & S_IRUSR));
	printf("usrw = %d\n", (bool)(buf.st_mode & S_IWUSR));
	printf("file = %d\n", (bool)(buf.st_mode & S_IFMT));
	if (buf.st_mode & S_IFDIR)
	{
		if (token->type == REDIR_L)
			ft_err("stdin", 8);
		else if (token->type == REDIR_R || token->type == REDIR_RD)
			ft_err(token->value, 8);
	}
	else if (create == -1 || (bool)(buf.st_mode & S_IFMT))
	{
		printf("%s\n", token->value);
		if ((create == -1 && token->type == REDIR_L)
			|| (((!(buf.st_mode & S_IRUSR) && token->type == REDIR_L)
			|| (!(buf.st_mode & S_IWUSR) && (token->type == REDIR_R
					|| token->type == REDIR_RD))) && !create))
			ft_err(token->value, 7); */
	buf = (struct stat){0};
	stat(tok->value, &buf);
	if ((buf.st_mode & S_IFDIR))
	{
		if (tok->type == REDIR_L)
		{
			ft_err("stdin", 8);
			remove_redir_tok(&tok);
			return (-1);
		}
		else if (tok->type == REDIR_R || tok->type == REDIR_RD)
		{
			ft_err(tok->value, 8);
			remove_redir_tok(&tok);
			return (-1);
		}
	}
	else if ((bool)(buf.st_mode & S_IFMT) || !buf.st_mode)
	{
/*		if (buf.st_mode && ((!(((bool)buf.st_mode & S_IRUSR)) && tok->type == REDIR_L)
			|| (!((bool)(buf.st_mode & S_IWUSR)) && (tok->type == REDIR_R
					|| tok->type == REDIR_RD)))) */
		if (!check_perm(tok->type, buf.st_mode))
		{
			ft_err(tok->value, 7);
			remove_redir_tok(&tok);
			return (-1);
		}
		else
		{
			if (tok->type == REDIR_R)
				return (open(path, O_CREAT | O_RDWR | O_TRUNC, 0644));
			if (tok->type == REDIR_RD)
				return (open(path, O_CREAT | O_RDWR | O_APPEND, 0644));
			if (tok->type == REDIR_L)
				return (open(path, O_RDONLY));
		}
	}
	return (-1);
}

static void	replace_fd(int *old, int new, int default_fd, bool *change)
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

int	skip_redir(t_pipe *pipe, t_token *tok)
{
	int			new_fd;

	while (tok && tok->type != PIPE)
	{
		if (tok->type == REDIR_RD || tok->type == REDIR_L
			|| tok->type == REDIR_R)
		{
			new_fd = try_open(tok, tok->value);
			if (new_fd == -1)
			{
				close_all_fd(pipe);
				return (-1);
			}
			if (tok->type == REDIR_RD || tok->type == REDIR_R)
				replace_fd(&pipe->fd_out, new_fd, 1, &pipe->out);
			else
				replace_fd(&pipe->fd_in, new_fd, 0, &pipe->in);
			remove_redir_tok(&tok);
		}
		else
			tok = tok->next;
		print_pipe(pipe);
	}
	return (0);
}
/*
stat(tok->value, &buf);
	if ((buf.st_mode & S_IFDIR))
	{
		if (tok->type == REDIR_L)
		{
			ft_err("stdin", 8);
			remove_redir_tok(tok);
			return (-1);
		}
		else if (tok->type == REDIR_R || tok->type == REDIR_RD)
		{
			ft_err(tok->value, 8);
			remove_redir_tok(tok);
			return (-1);
		}
	}
	else if ((bool)(buf.st_mode & S_IFMT))
	{
		if ((!(((bool)buf.st_mode & S_IRUSR)) && tok->type == REDIR_L)
			|| ((!((bool)(buf.st_mode & S_IWUSR)) && (tok->type == REDIR_R
					|| tok->type == REDIR_RD))))
		{
			ft_err(tok->value, 7);
			remove_redir_tok(tok);
			return (-1);
		}
		else
		{
			if (tok->type == REDIR_R)
			{
				new->fd_out = open(tok->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
				new->out = true;
				remove_redir_tok(tok);
				return (0);
			}
			else if (tok->type == REDIR_RD)
			{
				new->fd_out = open(tok->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
				new->out = true;
				remove_redir_tok(tok);
				return (0);
			}
			else if (tok->type == REDIR_L)
			{
				new->fd_out = open(tok->value, O_RDONLY);
				new->out = true;
				remove_redir_tok(tok);
				return (0);
			}
			if (tok->type == REDIR_RD || tok->type == REDIR_R)
				replace_fd(&pipe->fd_out, new_fd, 1, &pipe->out);
			else
				replace_fd(&pipe->fd_in, new_fd, 0, &pipe->in);
			remove_redir_tok(&tok);
		}
*/
