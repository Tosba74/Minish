/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_edit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 11:13:50 by bmangin           #+#    #+#             */
/*   Updated: 2021/11/28 18:36:26 by bmangin          ###   ########lyon.fr   */
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

static char	*choose_good_path(char **road_exec, char *av)
{
	int		i;
	int		fd_tmp;
	char	*tmp;

	i = -1;
	while (road_exec[++i])
	{
		tmp = ft_strjoin_free(road_exec[i], "/", 1);
		tmp = ft_strjoin_free(tmp, av, 1);
		if (tmp)
			fd_tmp = open(tmp, O_RDONLY | S_IRUSR | S_IRGRP | S_IROTH);
		if (fd_tmp > 0)
		{
			close(fd_tmp);
			free_all(road_exec, 0);
			return (tmp);
		}
		wrfree (tmp);
	}
	free_all(road_exec, 0);
	return (NULL);
}

char	*select_path(char *av)
{
	int		i;
	char	*road;
	char	**tmp;
	char	**road_exec;

	i = 0;
	road = NULL;
	tmp = ft_split(av, ' ');
	if (tmp)
	{
		road_exec = ft_split(env_find_cell(get_var_env(), "PATH")->value, ':');
		if (road_exec)
			road = choose_good_path(road_exec, tmp[0]);
		free_all(tmp, 0);
	}
	return (road);
}
