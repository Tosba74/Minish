/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:48:39 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/06 18:38:05 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_pipe	*new_cell_pipe(char *content)
{
	t_pipe	*new;

	new = wrmalloc(sizeof(t_pipe));
	new->pipe_line = ft_strdup(content);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->job = wrmalloc(sizeof(t_job));
	new->next = NULL;
	return (new);
}

t_pipe	*last_cell_pipe(t_pipe *pipe)
{
	if (pipe == NULL)
		return (NULL);
	while (pipe->next != NULL)
		pipe = pipe->next;
	return (pipe);
}

void	addback_cell_pipe(t_pipe **pipe, t_pipe *new)
{
	t_pipe	*last;

	last = last_cell_pipe(*pipe);
	if (last != NULL)
		last->next = new;
	else
		*pipe = new;
}

int	count_cell_pipe(t_pipe *pipe)
{
	int		count;

	count = 0;
	if (!pipe)
		return (count);
	while (pipe)
	{
		pipe = pipe->next;
		count++;
	}
	return (count);
}

void	free_pipeline(void)
{
	t_pipe	*p;

	if (!g_g->pipe)
		return ;
	while (g_g->pipe)
	{
		p = g_g->pipe;
		g_g->pipe = g_g->pipe->next;
		wrfree(p->pipe_line);
		wrfree(p);
	}
}
