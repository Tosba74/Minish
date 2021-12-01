/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 22:16:42 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/01 17:12:27 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
int	do_exit(t_job *j, int out)
{
	(void)j;
	(void)out;
	if (j->av[1] && !ft_isnum(j->av[1]))
		ft_putstr_fd("exit: numeric argument required\n", 2);
	else if (ft_strslen(j->av) > 2)
	{
		ft_err("exit", 0);
		return (E2BIG);
	}
	get_pid_exec()->exit = true;
	if (j->av[1])
		return (ft_atoi(j->av[1]));
	else
		return (0);
}
