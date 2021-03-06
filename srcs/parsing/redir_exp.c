/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 22:04:49 by bmangin          ###   ########lyon.fr   */
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

static int	redir_errors(struct stat buf, t_token **tok)
{
	if ((buf.st_mode & S_IFDIR))
	{
		if ((*tok)->type == REDIR_L)
		{
			ft_err("stdin", 8);
			remove_redir_tok(tok);
			return (0);
		}
		else if ((*tok)->type == REDIR_R || (*tok)->type == REDIR_RD)
		{
			ft_err((*tok)->value, 8);
			remove_redir_tok(tok);
			return (0);
		}
	}
	if (!buf.st_mode && (*tok)->type == REDIR_L)
	{
		get_pid_exec()->no_job = true;
		ft_err((*tok)->value, 6);
		remove_redir_tok(tok);
		return (0);
	}
	return (1);
}

static int	try_open(t_token *tok, char *path)
{
	struct stat	buf;

	buf = (struct stat){0};
	stat(tok->value, &buf);
	if (!redir_errors(buf, &tok))
		return (-1);
	else if (!buf.st_mode || (bool)(buf.st_mode & S_IFMT))
	{
		if (!check_perm(tok->type, buf.st_mode))
		{
			ft_err(tok->value, 7);
			remove_redir_tok(&tok);
			return (-1);
		}
		else
			return (open_redir(tok->type, path));
	}
	return (-1);
}

int	skip_redir(t_pipe *pipe, t_token *tok)
{
	int	new_fd;

	while (tok && tok->type != PIPE)
	{
		if (tok->type == REDIR_RD || tok->type == REDIR_L
			|| tok->type == REDIR_R || tok->type == REDIR_LD)
		{
			new_fd = try_open(tok, tok->value);
			if (new_fd == -1)
			{
				close_all_fd(pipe);
				return (-1);
			}
			if (tok->type == REDIR_LD)
				pipe->heredoc = ft_strdup(tok->value);
			else if (tok->type == REDIR_RD || tok->type == REDIR_R)
				replace_fd(&pipe->fd_out, new_fd, 1, &pipe->out);
			else if (tok->type == REDIR_L)
				replace_fd(&pipe->fd_in, new_fd, 0, &pipe->in);
			remove_redir_tok(&tok);
		}
		else
			tok = tok->next;
	}
	return (0);
}
