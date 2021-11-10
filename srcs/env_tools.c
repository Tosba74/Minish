/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:17:34 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/10 20:44:34 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

t_env	*new_cell_env(char **content, t_print print)
{
	t_env	*new;

	new = wrmalloc(sizeof(t_env));
	new->name = ft_strdup(content[0]);
	new->value = ft_strdup(content[1]);
	new->print = print;
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

int	env_size(t_env *env, int i)
{
	int		count;
	t_env	*cpy;

	count = 0;
	cpy = env;
	while (cpy)
	{
		if ((int)cpy->print < i)
			count++;
		cpy = cpy->next;
	}
	return (count);
}

t_env	**get_var_env(void)
{
	static t_env	*env;

	return (&env);
}
