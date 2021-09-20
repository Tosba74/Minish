/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:10:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/18 09:12:16 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	**split_content(const char *s)
{
	int		i;
	char	*tmp;
	char	**tab_tmp;

	i = -1;
	tab_tmp = ft_split(s, '=');
	if (tab_tmp == NULL)
		ft_err("Env: ", 2);
	tmp = ft_strdup(tab_tmp[0]);
	while (tmp[++i])
		if (!ft_isprint(tab_tmp[0][i]))
			ft_err("Env: ", 3);
	free_all(tab_tmp, ft_strslen(tab_tmp));
	tab_tmp = (char **)wrmalloc(sizeof(char *) * 3);
	tab_tmp[0] = tmp;
	tab_tmp[1] = ft_strdup(ft_strchr(s, '=') + 1);
	tab_tmp[2] = NULL;
	return (tab_tmp);
}

void	init_env(t_global *g, char **env)
{
	int		i;
	int		size;

	i = -1;
	size = ft_strslen(env);
	while (++i < size)
		addback_cell_env(&g->env, new_cell_env(split_content(env[i])));
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

char	**get_env_tab(t_env *env)
{
	int		i;
	t_env	*cpy;
	char	**tab;

	i = 0;
	cpy = env;
	tab = (char **)wrmalloc(sizeof(char *) * env_size(cpy) + 1);
	while (cpy)
	{
		tab[i] = get_env_line(cpy);
		cpy = cpy->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	print_envp(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	dprintf(STDERR_FILENO, "wc -l = %d & i = %d\n", ft_strslen(env), i);
}
