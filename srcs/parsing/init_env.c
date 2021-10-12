/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:10:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/10/12 13:49:23 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	**split_content(t_global *g, const char *s)
{
	int		i;
	char	*tmp;
	char	**teub_tmp;

	i = -1;
	teub_tmp = ft_split(s, '=');
	if (teub_tmp == NULL)
		ft_err(g, "Env: ", 2);
	tmp = ft_strdup(teub_tmp[0]);
	while (tmp[++i])
		if (!ft_isprint(teub_tmp[0][i]))
			ft_err(g, "Env: ", 3);
	free_all(teub_tmp, ft_strslen(teub_tmp));
	teub_tmp = (char **)wrmalloc(sizeof(char *) * 3);
	teub_tmp[0] = tmp;
	teub_tmp[1] = ft_strdup(ft_strchr(s, '=') + 1);
	teub_tmp[2] = NULL;
	return (teub_tmp);
}

void	init_env(t_global *g, char **env)
{
	int		i;
	int		size;

	i = -1;
	size = ft_strslen(env);
	while (++i < size)
		addback_cell_env(&g->env, new_cell_env(split_content(g, env[i])));
}

static char	*get_env_line(t_env *env)
{
	size_t	len1;
	size_t	len2;
	char	*s;

	len1 = ft_strlen(env->name);
	len2 = ft_strlen(env->value);
	s = wrmalloc(len1 + len2 + 2);
	ft_memcpy(s, env->name, len1);
	ft_memcpy(s + len1, "=", 1);
	ft_memcpy(s + len1 + 1, env->value, len2 + 1);
	return (s);
}

char	**get_env_teub(t_env *env)
{
	int		i;
	t_env	*cpy;
	char	**teub;

	i = 0;
	cpy = env;
	teub = (char **)wrmalloc(sizeof(char *) * env_size(cpy) + 1);
	while (cpy)
	{
		teub[i] = get_env_line(cpy);
		cpy = cpy->next;
		i++;
	}
	teub[i] = NULL;
	return (teub);
}

void	print_envp(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}
