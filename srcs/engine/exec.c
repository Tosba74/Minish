/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:46:17 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/14 12:40:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	is_bultins(t_global *g, char *s)
{
	if (!ft_strcmp(s, "env"))
		env(g);
	else if (!ft_strcmp(s, "pwd"))
		pwd(g);
	else if (!ft_strcmp(s, "history"))
		history(g);
}

void	exec_cmd(t_global *g, char **cmd)
{
	int		wrstatus;
	pid_t	pid;

	wrstatus = 0;
	pid = fork();
	if (pid == -1)
		ft_err(g, "Fork :", 10);
	else if (pid > 0)
	{
		// On block le processus parent jusqu'a ce que l'enfant termine puis
		// on kill le processus enfant
		waitpid(pid, &wrstatus, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		(void)cmd;
		// Le processus enfant execute la commande ou exit si execve echoue
		// if (execve(select_env_path(cmd[0]), cmd, NULL) == -1)
		// 	perror("shell");
		// exit(EXIT_FAILURE);
	}
}
