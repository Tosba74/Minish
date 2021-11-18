/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/18 18:20:38 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	print_token(t_token *tok)
{
	t_token	*cpy;

	cpy = tok;
	if (!cpy)
		dprintf(STDERR_FILENO, "\033[31mg->token is NULL, Bro!\033[0m\n");
	while (cpy != NULL)
	{
		if (cpy->type < 1)
			dprintf(STDERR_FILENO, "\033[32m%s|\033[0m", cpy->value);
		else if (cpy->type < 8)
			dprintf(STDERR_FILENO, "\033[34m%s|\033[0m", cpy->value);
		else if (cpy->type > 9 && cpy->type < 14)
			dprintf(STDERR_FILENO, "\033[36m%s|\033[0m", cpy->value);
		else if (cpy->type == 14)
			dprintf(STDERR_FILENO, "\033[93m%s|\033[0m", cpy->value);
		else
			dprintf(STDERR_FILENO, "\033[31m%s|\033[0m", cpy->value);
		cpy = cpy->next;
	}
	ft_putchar('\n');
}

void	print_envp(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		printf("%s\n", env[i]);
	}
}

void	debug(t_global *g, int i)
{
	void	(*pf[5])(void);

	pf[0] = print_env;
	pf[1] = print_env_teub;
	pf[2] = print_hidden;
	pf[3] = print_story;
	if (g->debug == true)
	{
		printf("debug activate\n");
		pf[i]();
	}
}
