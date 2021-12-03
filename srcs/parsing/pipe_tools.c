/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:48:39 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 21:51:25 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_pipe	*new_cell_pipe(t_token *tok)
{
	t_pipe	*new;

	(void)tok;
	new = wrmalloc(sizeof(t_pipe));
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->in = false;
	new->out = false;
	new->next = NULL;
	new->heredoc = NULL;
	new->save_in = 0;
	new->job = 0;
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

size_t	count_cell_pipe(t_pipe *pipe)
{
	size_t	count;

	count = 0;
	if (!pipe)
		return (count);
	while (pipe)
	{
		count++;
		pipe = pipe->next;
	}
	return (count);
}

void	clear_pipeline(t_pipe *pipe)
{
	t_pipe	*p;

	while (pipe)
	{
		p = pipe->next;
		del_job(pipe->job);
		wrfree(pipe);
		pipe = p;
	}
}
