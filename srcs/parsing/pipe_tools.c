/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:48:39 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/14 17:46:28 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_pipe	*new_cell_pipe(char *input, t_job *job)
{
	t_pipe	*new;

	new = wrmalloc(sizeof(t_pipe));
	new->pipe_line = input;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->in = true;
	new->out = true;
	if (!job)
		new->job = (t_job *){NULL};
	else
		new->job = job;
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

void	clear_pipeline(t_pipe *pipe)
{
	t_pipe	*p;

	if (pipe)
		return ;
	while (pipe)
	{
		p = pipe;
		pipe = pipe->next;
		del_job(p->job);
		wrfree(p->pipe_line);
		wrfree(p);
	}
}
