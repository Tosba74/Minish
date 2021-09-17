/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/16 19:15:13 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	cmp_env(char **env, char **envp)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp(envp[i], env[i]))
		{
			dprintf(STDERR_FILENO, "\033[31m|%s|\n|%s|\033[0m\n", envp[i], env[i]);
			return (1);
		}
		else
			dprintf(STDERR_FILENO, "\033[33m%s|\n|%s|\033[0m\n", envp[i], env[i]);
	}
	return (0);
}

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g = wrmalloc(sizeof(t_global));
	g = &(t_global){0};
	dprintf(STDERR_FILENO, "\033[32mTG OK\033[0m\n");
	if (ac == 2)
	{
		if (!strncmp(av[1], "-debug", 6))
			g->debug = true;
		else
			ft_err("Arg: ", 1);
	}
	init_env(g, env);
	debug(g, 1);
	debug(g, 0);
	print_envp(env);
	print_envp(get_env_tab(g->env));
	if (!cmp_env(get_env_tab(g->env), env))
		dprintf(STDERR_FILENO, "\033[32mYOUPI: env ok!!\033[0m");
	else
		dprintf(STDERR_FILENO, "\033[33menv ok\033[0m\n");
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	if (ac > 2)
		ft_err("Arg: ", 0);
	init_global(&g, ac, av, env);
	prompt();
	getchar();
	g.input = readline("$> ");
	printf("buf= %s\n", g.input);
	while (!g.input)
	{
		printf("buf2= %s\n", g.input);
		// parser(buf);
		prompt();
	}
}
