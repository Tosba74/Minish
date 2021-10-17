/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:48:39 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/17 15:34:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_pipe	*new_cell_pipe(char *content)
{
	t_pipe	*new;

	new = wrmalloc(sizeof(t_pipe));
	new->pipe_line = ft_strdup(content);
	new->fd_in = 0;
	new->fd_out = 1;
	new->job = wrmalloc(sizeof(t_job));
	new->next = NULL;
	return (new);
}

static t_pipe	*last_cell_pipe(t_pipe *pipe)
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
