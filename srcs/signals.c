/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:38:18 by astucky           #+#    #+#             */
/*   Updated: 2021/11/26 23:59:21 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	kill_fork(int sig)
{
	int	i;

	i = 0;
	while (i < get_pid_exec()->index)
	{
		kill(get_pid_exec()->pids[i], sig);
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit: 3\n", 1);
		else
		{
			ft_putstr_fd("\n", 1);
			g_err = 130;
		}
		i++;
	}
}

void	handler(int sig)
{
	if (get_pid_exec()->index && (sig == SIGINT || sig == SIGQUIT))
		kill_fork(sig);
}

void	handler_idle(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	g_err = 130;
	ft_putstr_fd(create_prompt(), 1);
}
