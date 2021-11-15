/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/15 22:06:31 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	waiting_pid(t_global *g)
{
	int	i;
	int	ret;
	int	wstatus;

	i = -1;
	while (++i < g->index)
	{
		waitpid(g->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			ret = (unsigned char)WEXITSTATUS(wstatus);
	}
	return (ret);
}

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
	int		i;
	char	*built[10];

	i = -1;
	built[0] = "echo";
	built[1] = "cd";
	built[2] = "pwd";
	built[4] = "export";
	built[5] = "unset";
	built[6] = "env";
	built[7] = "exit";
	built[8] = "history";
	built[9] = NULL;
	while (built[++i])
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
