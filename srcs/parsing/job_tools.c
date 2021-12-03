/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:51:29 by bmangin           #+#    #+#             */
/*   Updated: 2021/12/03 20:27:11 by bmangin          ###   ########lyon.fr   */
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
			get_road(new);
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

void	get_road(t_job *new)
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
