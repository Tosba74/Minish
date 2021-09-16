/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 19:07:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/15 15:13:29 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	print_env(t_global *g)
{
	t_env	*cpy;

	cpy = g->env;
	if (g->debug == true)
	{
		if (g->env == NULL)
			dprintf(STDERR_FILENO, "SHIT! g->env is NULL, Bro!\n");
		while (cpy->next)
			dprintf(STDERR_FILENO, "|%s| = |%s|\n", cpy->name, cpy->value);
	}
}

static void	print_hidden(t_global *g)
{
	t_env	*cpy;

	cpy = g->hidden;
	if (g->debug == true)
	{
		if (g->hide_mod == false)
			dprintf(STDERR_FILENO, "Hide mode is off, Bro!\n");
		if (cpy == NULL)
			dprintf(STDERR_FILENO, "g->hidden is NULL, Bro!\n");
		while (cpy->next)
			dprintf(STDERR_FILENO, "|%s| = |%s|\n", cpy->name, cpy->value);
	}
}

void	debug(t_global *g, int i)
{
	void	(*pf[2])(t_global *g);

	pf[0] = &print_env;
	pf[1] = &print_hidden;
	pf[i](g);
}
