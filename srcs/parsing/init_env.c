/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangin <bmangin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:10:12 by bmangin           #+#    #+#             */
/*   Updated: 2021/09/16 02:03:54 by bmangin          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

/*
static char	*split_content(char *s)
{
	char	**tab_tmp;
	int		i;
	int		index;
	int		stop;
	int		size;

	i = 0;
	index = 0;
	stop = 0;
	tab_tmp = (char **)wrmalloc(sizeof(char *) * 2)
	while (s[stop] != '=')
		stop++;
	tab_tmp[0] = wrmalloc(sizeof(char *) * (stop + 1));
	tab_tmp[1] = wrmalloc(sizeof(char *) * (size - stop));
	stop = 0;
	while (s[stop++])
	{
		if (s[stop] == '=')
		{
			if (index == 0)
			{
				tab_tmp[index][i] = 0;
				index++;
				i = 0;
			}
		}
		else
			tab_tmp[index][i] = s[stop];
	}
	dprintf(STDERR_FILENO, "%s = %s\n", tab_tmp[0], tab_tmp[1]);
	return (tab_tmp);
}
*/

static char	**split_content(const char *s)
{
	int		i;
	char	*tmp;
	char	**tab_tmp;

	i = -1;
	tab_tmp = ft_split(s, '=');
	if (tab_tmp == NULL)
		ft_err("Env: ", 2);
	tmp = tab_tmp[0];
	while (tmp[++i])
		if (!ft_isprint(tab_tmp[0][i]))
			ft_err("Env: ", 3);
	free_all(tab_tmp, ft_strslen(tab_tmp));
	tab_tmp = wrmalloc(sizeof(char *) * 3);
	tab_tmp[0] = tmp;
	tab_tmp[1] = ft_strdup(ft_strchr(s, '=') + 1);
	tab_tmp[2] = NULL;
	return (tab_tmp);
}

void	init_env(t_global *g, char **env)
{
	int		i;
	int		size;

	i = 0;
	size = ft_strslen(env);
	printf("size == %d\n", size);
	printf("%p\n", g->env);
	g->env = new_cell_env(split_content(env[i]));
	printf("%p\n", g->env);
	while (++i < size)
	{
		dprintf(STDERR_FILENO, "#%d||%s\n", i, env[i]);
		addback_cell_env(&g->env, new_cell_env(split_content(env[i])));
	}
}

char	**envlist_to_tab(t_env *env)
{
	int		i;
	t_env	*cpy;
	char	**tab;

	i = 0;
	cpy = env;
	tab = (char **)wrmalloc(sizeof(char *) * env_size(cpy));	
	while (cpy->next)
	{
		tab[i] = ft_strjoin_free(cpy->name, "=", 0);
		tab[i] = ft_strjoin_free(tab[i], cpy->value, 1);
		i++;
		cpy = cpy->next;
	}
	return (tab);
}
