/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:51:29 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/21 22:35:25 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*
void	del_job(t_job *jobs)
{
	int	len;

	len = ft_strslen(jobs->av);
	if (len != 0)
	{
		while (len-- != 0)
			ft_memdel(jobs->av[len]);
	}
	ft_memdel(jobs->av);
	ft_memdel(jobs);
}

t_job	*new_job(char **av)
{
	t_job	*new;

	new = (t_job *)wrmalloc(sizeof(t_job));
	new->av = av++;
	new->flags = NULL;
	new->envp = NULL;
	return (new);
}
*/

void	del_job(t_job *jobs)
{
	int	len;

	len = ft_strslen(jobs->av);
	if (len != 0)
	{
		while (len-- != 0)
			ft_memdel(jobs->av[len]);
	}
	ft_memdel(jobs->av);
	ft_memdel(jobs);
}

t_job	*new_job(char *av)
{
	t_job	*new;
	int		vret;

	new = (t_job *)wrmalloc(sizeof(t_job));
	new->av = ft_split(av, ' ');
	vret = is_builtin(new->av[0]);
	if (vret == -1)
		new->is_cmd = true;
	else
		new->is_cmd = false;
	if (new->is_cmd)
		new->job = select_env_path(av, get_env_teub(*get_var_env(), 1));
	else
		new->job = ft_strdup(new->av[0]);
	return (new);
}

int	count_cell_tok(t_token *tok)
{
	int		count;

	count = 0;
	if (!tok)
		return (count);
	while (tok)
	{
		tok = tok->next;
		count++;
	}
	return (count);
}

void	print_pipe(t_pipe *p)
{
	t_pipe	*cpy;
	int		i;

	cpy = p;
	// while (cpy)
	// {
		i = -1;
		// printf("| input = %27s |\n", cpy->pipe_line);
		printf("|  cmd = %28s |\n", cpy->job->job);
		while (cpy->job->av[++i])
			printf("| av[%d]  %28s |\n", i, cpy->job->av[i]);
		printf("| is_cmd = %3d                        |\n", cpy->job->is_cmd);
		printf("| bool_in = %3d     bool_ out = %3d   |\n", cpy->in, cpy->out);
		printf("| fd_in = %3d       fd_ out = %3d     |\n",
			cpy->fd_in, cpy->fd_out);
		// cpy = cpy->next;
	// }
}
