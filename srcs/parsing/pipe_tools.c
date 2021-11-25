/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:48:39 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/24 19:00:32 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_pipe	*new_cell_pipe(t_token *tok)
{
	t_pipe	*new;

	new = wrmalloc(sizeof(t_pipe *));
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->in = false;
	new->out = false;
	new->job = wrmalloc(sizeof(t_job *));
	new->job->av = complet_av(tok);
	if (new->job->av[0])
	{
		if (is_builtin(new->job->av[0]) == -1)
		{
			new->job->job = select_env_path(new->job->av[0],
					get_env_teub(*get_var_env(), 1));
			new->job->is_cmd = true;
		}
		else
		{
			new->job->job = new->job->av[0];
			new->job->is_cmd = false;
		}
	}
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
		wrfree(p);
	}
}
