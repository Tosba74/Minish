/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/12 09:56:33 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

bool	g_debug = false;
int		g_err = 0;

static const char	*prompt(void)
{
	char	*prompt;

	if (g_err == 0)
		prompt = "\033[36m$\033[0m\033[34m>\033[0m ";
	else
		prompt = "\033[31m$\033[0m\033[33m>\033[0m ";
	return (prompt);
}

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g_debug = false;
	(void)g;
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "-debug", 6))
			g_debug = true;
		else
		{
			ft_err("Arg", 1);
			exit (g_err);
		}
	}
	init_env(env);
	debug(0);
	debug(1);
}

/*
void	init_pipe_bluff(char *input)
{
	t_pipe	*tmp;

	addback_cell_pipe(&g_g->pipe, new_cell_pipe(input));
	tmp = last_cell_pipe(g_g->pipe);
	tmp->job->job = input;
	tmp->job->av = ft_split(input, ' ');
}
*/

static void	loop(t_global *g)
{
	int		i;
	char	*input;
	t_pipe	*pipe;

	i = 0;
	input = readline(prompt());
	while (input)
	{
		pipe = &(t_pipe){0};
		if (input[0])
		{
			add_history(input);
			addback_cell_history(get_history(),
				new_cell_history(skip_space(input), i++));
			parser(pipe);
			// (void)g;
			// if (count_cell_pipe(pipe) == 1)
				// simple_cmd(pipe);
			// else
				// exec(g, pipe);
			exec(g, pipe);
		}
		clear_pipeline(pipe);
		wrfree(input);
		input = readline(prompt());
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	g = (t_global){};; 
	if (ac > 2)
	{
		ft_err("Arg", 0);
		exit(1);
	}
	init_global(&g, ac, av, env);
	loop(&g);
	wrdestroy();
	return (g_err);
}
