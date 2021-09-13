/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 18:33:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/14 00:38:52 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init_global(t_global *g, char **env)
{
	g = wrmalloc(sizeof(t_global));
	printf("TG OK\n");
	// init_env(g->env, env);
	printf("env ok\n");
	(void)env;
}

int	main(int ac, char **av, char **env)
{
	t_global	g;
	char		*buf;
	size_t		buf_size;

	if (ac > 1)
		ft_err("Arg: ", 0);
	(void)av;
	init_global(&g, env);
	buf_size = 2048;
	buf = (char *)ft_calloc(sizeof(char), buf_size);
	prompt();
	while (getline(&buf, &buf_size, stdin) > 0)
	{
		printf("buf = %s\n", buf);
		parser(buf);
		prompt();
	}
	wrfree(buf);
}
