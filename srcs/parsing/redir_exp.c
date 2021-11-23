/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:10:42 by bmangin           #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2021/11/23 15:26:08 by astucky          ###   ########lyon.fr   */
=======
/*   Updated: 2021/11/23 16:25:27 by bmangin          ###   ########lyon.fr   */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

<<<<<<< Updated upstream
/* PETIT RECAP DES MODIFS

gestion d'erreurs:
access(path, F_OK) renvoie 0 si le fichier existe ou -1 s'il n'existe pas
du coup tu peux poser l'erreur "no such file or directory" en te servant de la valeur de create

boucle inf:
maintenant remove_redir_tok prend en parametre un t_token **
sinon tok ne passe pas a l'addresse suivante dans skip_redir, et du coup on se retrouve avec un pointeur vide, ce qui occasionnait un -1...

*/

static int	try_open(t_token *token, char *path)
=======
/*
static int	try_open(t_pipe *p, t_token *token, char *path)
>>>>>>> Stashed changes
{
	struct stat	buf;
	int			create;

<<<<<<< Updated upstream
	create = access(path, F_OK);
	buf.st_mode = 0;
	if (!create)
		stat(token->value, &buf);
=======
	printf("%s\n", token->value);
	stat(token->value, &buf);
>>>>>>> Stashed changes
	printf("dire = %d\n", (bool)(buf.st_mode & S_IFDIR));
	printf("file = %d\n", (bool)(buf.st_mode & S_IFMT));
	printf("usrr = %d\n", (bool)(buf.st_mode & S_IRUSR));
	printf("usrw = %d\n", (bool)(buf.st_mode & S_IWUSR));
	if ((bool)(buf.st_mode & S_IFDIR))
	{
		if (token->type == REDIR_L)
			ft_err("stdin", 8);
		else if (token->type == REDIR_R || token->type == REDIR_RD)
			ft_err(token->value, 8);
	}
	else if (create == -1 || (bool)(buf.st_mode & S_IFMT))
	{
		printf("%s\n", token->value);
<<<<<<< Updated upstream
		if ((create == -1 && token->type == REDIR_L)
			|| (((!(buf.st_mode & S_IRUSR) && token->type == REDIR_L)
			|| (!(buf.st_mode & S_IWUSR) && (token->type == REDIR_R
					|| token->type == REDIR_RD))) && !create))
=======
		if ((!(((bool)buf.st_mode & S_IRUSR)) && token->type == REDIR_L)
			|| ((!((bool)(buf.st_mode & S_IWUSR)) && (token->type == REDIR_R
					|| token->type == REDIR_RD))))
>>>>>>> Stashed changes
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

static void	replace_fd(int *old, int new, int default_fd, bool *change)
{
	if (*old != default_fd)
		close(*old);
	*old = new;
	*change = true;
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

	// while (tok && tok->type != PIPE)
	// {
	// 	if (9 < tok->type || tok->type < 13)
	// 	{
			if (tok->value[0] == '$')
				ft_err(tok->value, 9);
			else
			{
				new_fd = try_open(tok, tok->value);
				printf("ret try_open = %d\n	", new_fd);
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
	// 	}
	// 	else
	// 		tok = tok->next;
	// }
	return (1);
}

int	skip_redir(t_pipe *pipe, t_pipe *new, t_token *tok)
{
	int			new_fd;

	while (tok && !(9 < tok->type && tok->type < 14))
		tok = tok->next;
	printf("%s\n", tok->value);
	if (tok->value[0] == '$')
		ft_err(tok->value, 9);
	else
	{
		new_fd = try_open(pipe, tok, tok->value);
		printf("ret try_open = %d\n	", new_fd);
		if (new_fd == -1 || !check_read(new_fd))
		{
			close_all_fd(new);
			return (0);
		}
		if (tok->type == REDIR_RD || tok->type == REDIR_R)
			replace_fd(&new->fd_out, new_fd, 1);
		else
			replace_fd(&new->fd_in, new_fd, 0);
		remove_redir_tok(tok);
	}
	return (1);
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
*/

static void	remove_redir_tok(t_token *tok)
{
	t_token	*next;

	next = tok->next;
	remove_cell_tok(tok);
	tok = next;
}

int	skip_redir(t_pipe *new, t_token *tok)
{
	struct stat	buf;

	while (!(9 < tok->type && tok->type < 14))
		tok = tok->next;	
	if (!ft_strncmp(tok->value, "$", 1) && tok->type != REDIR_LD)
	{
		ft_err(tok->value, 9);
		remove_redir_tok(tok);
		return (-1);
	}
	printf("t->v => %s\n", tok->value);
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
		else
			tok = tok->next;
		print_pipe(pipe);
	}
	return (-1);
}

/*
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
	printf("file = %d\n", (buf.st_mode & S_IFMT));
	printf("usrr = %d\n", (buf.st_mode & S_IRUSR));
	printf("usrw = %d\n", (buf.st_mode & S_IWUSR));
	// printf("%d \n", try_open(tok, tok->value));
	print_token(tok);
	next = tok->next;
	remove_cell_tok(tok);
	tok = next;
	(void)new;
	return (1);
}
*/