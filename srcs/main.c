/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/20 11:31:14 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	cmp_env(char **env, char **envp)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strcmp(envp[i], env[i]))
			return (1);
	return (0);
}

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g = wrmalloc(sizeof(t_global));
	g = &(t_global){0};
	g->envp = env;
	dprintf(STDERR_FILENO, "\033[32minti TG!\033[0m\n");
	if (ac == 2)
	{
		if (!ft_strncmp(av[1], "-debug", 6))
			g->debug = true;
		else
		{
			ft_err(g, "Arg: ", 1);
			exit (g->err);
		}
	}
	init_env(g, env);
	// debug(g, 0);
	// debug(g, 1);
	if (!cmp_env(get_env_teub(g->env), env))
		dprintf(STDERR_FILENO, "\033[32mYOUPI: env OK!!\n\033[0m");
	else
		dprintf(STDERR_FILENO, "\033[33menv ko!!\n\033[0m\n");
}

static void	loop(t_global *g)
{
	int		i;
	char	*input;

	i = 0;
	input = readline(prompt());
	while (input)
	{
		add_history(input);
		addback_cell_history(&g->history, new_cell_history(input, i++));
		parser(g);
		debug(g, 5);
		// is_bultins(g, input);
		wrfree(input);
		input = readline(prompt());
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	g = (t_global){0};
	if (ac > 2)
	{
		ft_err(&g, "Arg: ", 0);
		exit(g.err);
	}
	init_global(&g, ac, av, env);
	loop(&g);
	wrdestroy();
	return (0);
}
