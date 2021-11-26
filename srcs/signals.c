/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:38:18 by astucky           #+#    #+#             */
/*   Updated: 2021/11/26 19:57:13 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void kill_fork(int sig)
{
	int	i;
	
	i = 0;
	while (i < get_pid_exec()->index)
	{
		kill(get_pid_exec()->pids[i], sig);
		if (sig == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_err = 131;
		}
		else
		{
			ft_putstr_fd("\n", 1);
			g_err = 130;
		}
		i++;
	}
	ft_putstr_fd(create_prompt(), 1);
}

void	handler(int sig)
{
	if (get_pid_exec()->index && (sig == SIGINT || sig == SIGQUIT))
		kill_fork(sig);
	else if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_err = 130;
		ft_putstr_fd(create_prompt(), 1);
	}
	else
	{
		ft_putstr_fd("\r", 1);
		ft_putstr_fd(create_prompt(), 1);
	}
}
