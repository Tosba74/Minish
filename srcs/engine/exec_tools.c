/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/26 17:41:38 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	dup_close(int src, int dst, char *s)
{
	if (dup2(src, dst) < 0)
		ft_err(s, 14);
	if (close (src) < 0)
		ft_err(s, 14);
}

void	skip_slash(char *av)
{
	int		i;

	i = ft_strlen(av) - 1;
	if (av[i] == '/')
		av[i] = '\0';
}

int	is_builtin(char *s)
{
	int					i;
	static const char	*built[] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		"history"
	};

	i = -1;
	if (s)
		while (++i < (int)(sizeof(built) / sizeof(*built)))
			if (!ft_strcmp(built[i], s))
				return (i);
	return (-1);
}

int	select_built(t_pipe *p)
{
	int		(*pf_built[8])(t_job *j);

	pf_built[0] = do_echo;
	pf_built[1] = do_cd;
	pf_built[2] = pwd;
	pf_built[3] = export;
	pf_built[4] = unset;
	pf_built[5] = env;
	pf_built[6] = do_exit;
	pf_built[7] = history;
	return (pf_built[is_builtin(p->job->job)](p->job));
}

int	waiting_pid(t_global *g)
{
	int	i;
	int	ret;
	int	wstatus;

	i = 0;
	while (++i < g->index)
	{
		waitpid(get_pid_exec[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			ret = (unsigned char)WEXITSTATUS(wstatus);
	}
	return (ret);
}

/*
static void	init_fd(t_pipe *pipe, char *file1, char *file2)
{
	t_pipe	*p;
	int		fd_tmp;

	p = pipe;
	p->fd_in = open (file1, O_DIRECTORY);
	if (p->fd_in > 0)
	{
		close(p->fd_in);
		ft_err("File opening:\n", 0);
	}
	close(p->fd_in);
	p->fd_in = open(file1, O_RDONLY);
	fd_tmp = p->fd_in;
	p = last_cell_pipe(p);
	p->fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd_tmp == -1 || p->fd_out == -1)
	{
		close(fd_tmp);
		close(p->fd_out);
	}
}

int	pipex(int ac, char **av, char **env)
{
	int		i;
	t_pipe	*p;
	t_pipe	*cpy;

	i = 1;
	p = NULL;
	while (i++ < ac - 2)
	{
		addback_cell_pipe(&p,
			new_cell_pipe(av[i], new_job(av[i], env)));
	}
	init_fd(p, av[1], av[ac - 1]);
	i = 1;
	cpy = p;
	while (i++ < ac - 2)
	{
		if (i == 2)
			cpy->in = false;
		if (i == ac - 2)
			cpy->out = false;
		cpy = cpy->next;
	}
	print_pipe(p);
	return (exec(p, ac, env));
}
*/
