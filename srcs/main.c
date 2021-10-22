/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/22 12:11:40 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static const char	*prompt(void)
{
	char	*prompt;

	prompt = "\033[36m$\033[0m\033[34m>\033[0m ";
	return (prompt);
}

static void	init_global(int ac, char **av, char **env)
{
	g_g = wrmalloc(sizeof(t_global));
	g_g = &(t_global){0};
	g_g->envp = env;
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "-debug", 6))
			g_g->debug = true;
		else
		{
			ft_err("Arg: ", 1);
			exit (g_g->err);
		}
	}
	init_env(g_g, env);
	debug(0);
	debug(1);
}

void	init_pipe_bluff(char *input)
{
	t_pipe	*tmp;

	addback_cell_pipe(&g_g->pipe, new_cell_pipe(input));
	tmp = last_cell_pipe(g_g->pipe);
	tmp->job->job = input; 
	tmp->job->av = ft_split(input, ' ');

}

static void	loop(void)
{
	int		i;
	char	*input;

	i = 0;
	input = readline(prompt());
	while (input)
	{
		add_history(input);
		addback_cell_history(&g_g->history, new_cell_history(input, i++));
		parser();
		// debug(5);
		init_pipe_bluff("ls");
		exec();
		// is_bultins(g, input);
		wrfree(input);
		input = readline(prompt());
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac > 2)
	{
		ft_err("Arg: ", 0);
		exit(g_g->err);
	}
	init_global(ac, av, env);
	loop();
	wrdestroy();
	return (0);
}
