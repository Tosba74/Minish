/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/08 22:19:10 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_global	*g_g = &(t_global){0};

static const char	*prompt(void)
{
	char	*prompt;

	prompt = "\033[36m$\033[0m\033[34m>\033[0m ";
	return (prompt);
}

static void	init_global(int ac, char **av, char **env)
{
	g_g->envp = env;
	g_g->debug = false;
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "-debug", 6))
			g_g->debug = true;
		else
		{
			ft_err("Arg", 1);
			exit (g_g->err);
		}
	}
	init_env(g_g, env);
	printf("lst env = %p lst hide = %p\n",g_g->env, g_g->hidden);
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
		if (input[0])
		{
			add_history(input);
			addback_cell_history(&g_g->history, new_cell_history(skip_space(input), i++));
			parser(skip_space(input));
			// init_pipe_bluff("ls");
			exec();
			// is_bultins(g, input);
		}
		wrfree(input);
		input = readline(prompt());
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac > 2)
	{
		ft_err("Arg", 0);
		exit(1);
	}
	init_global(ac, av, env);
	loop();
	wrdestroy();
	return (0);
}
