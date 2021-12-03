/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:32:56 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 20:29:41 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

int	simple_cmd(t_global *g, t_pipe *pipe)
{
	(void)g;
	(void)pipe;
	g_err = select_built(pipe);
	return (g_err);
}

t_pids	*get_pid_exec(void)
{
	static t_pids	p;

	return (&p);
}
