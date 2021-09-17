/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:17:34 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/16 22:00:03 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_env	*new_cell_env(char **content)
{
	t_env	*new;

	new = wrmalloc(sizeof(t_env));
	dprintf(STDERR_FILENO, "\033[32m|%s||%s|\033[0m\n", content[0], content[1]);
	new->name = content[0];
	new->value = content[1];
	new->next = NULL;
	return (new);
}

static t_env	*last_cell_env(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	addback_cell_env(t_env **env, t_env *new)
{
	t_env	*last;

	last = last_cell_env(*env);
	if (last != NULL)
		last->next = new;
	else
		*env = new;
}

int	env_size(t_env *env)
{
	int		count;
	t_env	*cpy;

	count = 0;
	cpy = env;
	if (cpy == NULL)
		return (0);
	while (cpy != NULL)
	{
		cpy = cpy->next;
		count++;
	}
	return (count);
}
