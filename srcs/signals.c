/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astucky <astucky@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:38:18 by astucky           #+#    #+#             */
/*   Updated: 2021/11/26 18:29:50 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void kill_fork(int sig)
{
	(void)sig;
	return ;
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
		ft_putstr_fd("\b ", 1);
	}
}
