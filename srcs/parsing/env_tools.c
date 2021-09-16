/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:17:34 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/16 02:05:48 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_env	*new_cell_env(char **content)
{
	t_env	*new;

	new = wrmalloc(sizeof(t_env));
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
	dprintf(STDERR_FILENO, "New cell %p\n", new);
	if (last != NULL)
	{
		last->next = new;
		dprintf(STDERR_FILENO, "New cell with new %p\n", last->next);
	}
	else
	{
		*env = new;
		dprintf(STDERR_FILENO, "Create list with new %p\n", *env);
	}
}

int	env_size(t_env *env)
{
	int		count;

	count = 0;
	if (env == NULL)
		return (0);
	while (env != NULL)
	{
		env = env->next;
		count++;
	}
	return (count);
}