/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/14 19:24:55 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init_global(t_global *g, int ac, char **av, char **env)
{
	g = wrmalloc(sizeof(t_global));
	printf("TG OK\n");
	if (ac == 2 && !strncmp(av[1], "-debug", 6))
		g->debug = true;
	init_env(&g->env, env);
	printf("env ok\n");
	print_env(g, g->env);
	(void)env;
}

int	main(int ac, char **av, char **env)
{
	t_global	g;

	if (ac > 2)
		ft_err("Arg: ", 0);
	init_global(&g, ac, av, env);
	prompt();
	// g.input = readline("$> ");
	// printf("buf2= %s\n", g.input);
	while (!g.input)
	{
		printf("buf2= %s\n", g.input);
		// parser(buf);
		prompt();
	}
}
