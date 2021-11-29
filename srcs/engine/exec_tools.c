/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/29 00:48:32 by bmangin          ###   ########lyon.fr   */
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
		"history",
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
	int				index;
	static int		(*pf_built[8])(t_job *j, int out);

	pf_built[0] = do_echo;
	pf_built[1] = do_cd;
	pf_built[2] = pwd;
	pf_built[3] = do_export;
	pf_built[4] = unset;
	pf_built[5] = env;
	pf_built[6] = do_exit;
	pf_built[7] = history;
	index = is_builtin(p->job->job);
	return (pf_built[index](p->job, p->fd_out));
}

int	waiting_pid(void)
{
	int	i;
	int	ret;
	int	wstatus;

	i = -1;
	while (++i < get_pid_exec()->index)
	{
		waitpid(get_pid_exec()->pids[i], &wstatus, 0);
		if (WIFEXITED(wstatus))
			ret = (unsigned char)WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			ret = (unsigned char)WTERMSIG(wstatus) + 128;
	}
	return (ret);
}

t_pids	*get_pid_exec(void)
{
	static t_pids	p;

	return (&p);
}
