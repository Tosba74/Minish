/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:51:29 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 19:56:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	del_job(t_job *jobs)
{
	free_all(jobs->av, 0);
	jobs->is_cmd = false;
	jobs->is_built = false;
	wrfree(jobs->job);
	wrfree(jobs);
}

void	built_job(t_job *pipe, char *s)
{
	pipe->job = ft_strdup(s);
	pipe->is_cmd = false;
	pipe->is_built = true;
}

t_job	*new_job(t_token *tok)
{
	t_job	*new;

	new = wrmalloc(sizeof(t_job));
	new->av = complet_av(tok);
	if (new->av[0])
	{
		if (is_builtin(new->av[0]) == -1)
		{
			if (new->av[0][0] == '/')
				new->job = ft_strdup(new->av[0]);
			else
				new->job = select_path(new->av[0]);
			if (new->job)
				new->is_cmd = true;
			else
			{
				get_pid_exec()->no_job = true;
				ft_err(new->av[0], 13);
			}
			new->is_built = false;
		}
		else
			built_job(new, new->av[0]);
	}
	free_all(new->av, 0);
	return (new);
}

int	count_cell_tok(t_token *tok)
{
	int		count;

	count = 0;
	if (!tok)
		return (count);
	while (tok && tok->type != PIPE)
	{
		if (tok->type != SPC)
			count++;
		tok = tok->next;
	}
	return (count);
}

void	print_pipe(t_pipe *p)
{
	t_pipe	*cpy;
	int		i;

	cpy = p;
	i = -1;
	printf("|  cmd = %28s |\n", cpy->job->job);
	while (cpy->job->av[++i])
		printf("| av[%d]  %28s |\n", i, cpy->job->av[i]);
	printf("| is_cmd = %3d      is_built = %3d    |\n",
		cpy->job->is_cmd, cpy->job->is_built);
	printf("| bool_in = %3d     bool_ out = %3d   |\n", cpy->in, cpy->out);
	printf("| fd_in = %3d       fd_ out = %3d     |\n", cpy->fd_in, cpy->fd_out);
}
