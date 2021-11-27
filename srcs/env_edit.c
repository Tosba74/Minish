/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:13:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/27 17:31:38 by astucky          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	remove_cell_env(char *name, t_env *env)
{
	t_env	*copy;
	int		namelen;

	namelen = ft_strlen(name);
	if (!env)
		return ;
	while (env && ft_strncmp(env->name, name, namelen + 1))
	{
		copy = env;
		env = env->next;
	}
	if (env)
	{
		copy->next = env->next;
		wrfree(env->name);
		wrfree(env->value);
		wrfree(env);
	}
}

t_env	*env_find_cell(t_env **env, char *name)
{
	t_env	*tmp;
	int		namelen;
	int		envlen;

	tmp = *env;
	namelen = ft_strlen(name);
	while (tmp)
	{
		envlen = ft_strlen(tmp->name);
		if (envlen >= namelen && !ft_strncmp(tmp->name, name, namelen + 1))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_edit_value(t_env *env, char *value)
{
	wrfree(env->value);
	env->value = ft_strdup(value);
}
