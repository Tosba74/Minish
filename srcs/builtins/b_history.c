/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_history.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:03:08 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/26 22:24:35 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_story(int out)
{
	t_story	*history;

	history = *get_history();
	ft_putstr_fd("\033[34m-----  HISTORY  ------\033[0m\n", out);
	while (history)
	{
		ft_putstr_fd("\033[33m#", out);
		ft_putnbr_fd(history->index, out);
		ft_putstr_fd("\033[32m", out);
		ft_putstr_fd(history->cmd, out);
		ft_putstr_fd("\033[0m\n", out);
		history = history->next;
	}
}

int	history(t_job *j, int out)
{
	(void)j;
	print_story(out);
	return (0);
}
