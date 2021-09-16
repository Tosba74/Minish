/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/15 18:36:34 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_envp(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		dprintf(STDERR_FILENO, "%s\n", env[i]);
	dprintf(STDERR_FILENO, "wc -l = %d\n", ft_strslen(env));
}

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g = wrmalloc(sizeof(t_global));
	printf("TG OK\n");
	if (ac == 2)
	{
		if (!strncmp(av[1], "-debug", 6))
			g->debug = true;
		else
			ft_err("Arg: ", 1);
	}
	print_envp(env);
	init_env(g, env);
	printf("env ok\n");
	debug(g, 0);
	debug(g, 1);
	(void)env;
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	if (ac > 2)
		ft_err("Arg: ", 0);
	init_global(&g, ac, av, env);
	prompt();
	g.input = readline("$> ");
	// printf("buf2= %s\n", g.input);
	while (!g.input)
	{
		printf("buf2= %s\n", g.input);
		// parser(buf);
		prompt();
	}
}
