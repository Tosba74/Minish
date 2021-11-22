/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/22 16:59:52 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/* PETIT RECAP DES MODIFS

gestion d'erreurs:
access(path, F_OK) renvoie 0 si le fichier existe ou -1 s'il n'existe pas
du coup tu peux poser l'erreur "no such file or directory" en te servant de la valeur de create

boucle inf:
maintenant remove_redir_tok prend en parametre un t_token **
sinon tok ne passe pas a l'addresse suivante dans skip_redir, et du coup on se retrouve avec un pointeur vide, ce qui occasionnait un -1...

*/

static int	try_open(t_token *token, char *path)
{
	struct stat	buf;
	int			create;

	create = access(path, F_OK);
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
			ft_err(token->value, 7);
		else
		{
			if (token->type == REDIR_R)
				return (open(path, O_CREAT | O_RDWR | O_TRUNC, 0644));
			if (token->type == REDIR_RD)
				return (open(path, O_CREAT | O_RDWR | O_APPEND, 0644));
			if (token->type == REDIR_L)
				return (open(path, O_RDONLY));
		}
	}
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
			if (new_fd == -1 || !check_read(new_fd))
			{
				close_all_fd(pipe);
				return (0);
			}
			if (tok->type == REDIR_RD || tok->type == REDIR_R)
				replace_fd(&pipe->fd_out, new_fd, 1);
			else
				replace_fd(&pipe->fd_in, new_fd, 0);
			remove_redir_tok(&tok);
		}
		else
			tok = tok->next;
	}
	return (1);
}
