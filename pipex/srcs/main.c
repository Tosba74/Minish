/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 04:40:14 by bmangin           #+#    #+#             */
/*   Updated: 2021/08/17 18:15:46 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_fd(t_pipex *p, char *file1, char *file2)
{
	p->fd_in = open (file1, O_DIRECTORY);
	if (p->fd_in > 0)
	{
		close(p->fd_in);
		ft_err("File opening:\n", 0);
	}
	close(p->fd_in);
	p->fd_in = open(file1, O_RDONLY);
	p->fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (p->fd_in == -1 || p->fd_out == -1)
	{
		close(p->fd_in);
		close(p->fd_out);
	}
}

int	pipex(int ac, char **av, char **env)
{
	t_pipex	p;

	p = (t_pipex){};
	init_fd(&p, av[1], av[ac - 1]);
	return (exec(&p, ac, av, env));
}

int	main(int ac, char **av, char **env)
{
	if (ac > 4)
		return (pipex(ac, av, env));
	else
		ft_err("Command: ", 2);
	return (0);
}
