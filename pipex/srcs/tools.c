/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:13:31 by bmangin           #+#    #+#             */
/*   Updated: 2021/08/16 16:30:16 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static const char	*msg_err(int err)
{
	static const char	*tab[] = {
	"Dude! Use \"file\" pls!\n",
	"invalid file\n",
	"./pipex file1 \"cmd1\" \"cmd2\" file2\n",
	"Pipe error\n",
	"Fork error\n",
	"ZOMBIE Child\n",
	"Dude!? what's is this cmd?\n",
	"Dup failed: I think, you want to dup a closed fd\n",
	"Close failed: Your fd is already closed or not open\n"
	};

	return (tab[err]);
}

void	ft_err(char *s, int err)
{
	ft_putstr_fd("Error:\n", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd((char *)msg_err(err), STDERR_FILENO);
	wrdestroy();
	exit(0);
}

void	init_bool(t_pipex *p, int index, int ac)
{
	p->in = true;
	p->out = true;
	if (index == 2)
		p->in = false;
	else if (index == ac - 2)
		p->out = false;
}

void	init_cmd(t_pipex *p, char *av)
{
	if (p->cmd)
		ft_memdel(p->cmd);
	if (p->av)
		ft_memdel(p->av);
	p->av = ft_split(av, ' ');
	p->cmd = select_env_path(av, p->env);
	if (!p->cmd || !p->av)
		ft_err("Command: ", 6);
}

void	dup_close(int src, int dst, char *s)
{
	if (dup2(src, dst) < 0)
		ft_err(s, 7);
	if (close (src) < 0)
		ft_err(s, 8);
}
